#include "game.h"
#include <algorithm>
#include <memory>
#include <random>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDateTime>

Game::Game(QObject *parent)
    : QObject{parent}, m_handEvaluator(std::make_unique<HandEvaluator>())
{
    gamerCount = 0;
    round = 0;
    hand = 0;
    handPart = 0;
    removedCardsNum = 0;
    readyGamers = 0;
    roundOverRecived = 0;

    gamers.clear();
    randomSelectionCount.clear();
    stopUsageCount.clear();

    connect(this,SIGNAL(newGamerAdded()),this,SLOT(newGamerAddedSlot()));
    for(int i=0; i<=3 ; i++){
        for(int j=0; j<=12 ;j++){
            cards.push_back(Card(i,j));
        }
    }
}

void Game::addGamer(qintptr id, QString username)
{
    gamers.push_back(new Gamer(id,username));
    gamerCount++;
    qDebug()<<"added gamer";
    emit newGamerAdded();
}

void Game::remGamer(QString username)
{
    for(int i=0;i<gamerCount;i++)
    {
        if(gamers[i]->getUserName() == username)
        {
            gamers.remove(i);
            break;
        }
    }
    gamerCount--;
}

void Game::addNewOnlineUser(qintptr id, MyThread *thread)
{
    _onlineUsers.insert(id,thread);
    qDebug()<<"thread"<<thread<<"id"<<id;
}

void Game::sendToGamer(qintptr _id, const QString data)
{
    qDebug()<<"want to send";
    if(_onlineUsers.contains(_id)){
        qDebug()<<_id <<"is there";
        QMetaObject::invokeMethod(_onlineUsers[_id], "writeToSocket", Qt::QueuedConnection, Q_ARG(QByteArray, data.toUtf8()));
        qDebug()<<"send to gamer"<<gamers[_id]->getUserName()<<" "<<data;
    }
}

void Game::startGame()
{
    round = 1;
    hand = 1;
    handPart = 0;
    shuffle(cards);
    makeNewCardStr();
    gameManager();
}

void Game::shuffle(QVector<Card> &_cards)
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::shuffle(_cards.begin(),_cards.end(),rng);
}

void Game::makeNewCardStr()
{
    cardStr = "cards_data";
    for(int i=removedCardsNum,j=0;j<7;j++,i++){
        cardStr+=";"+ cards[i].toString();
    }
    removedCardsNum+=7;
}

void Game::updateCardStr(QString selectedCard)
{
    QStringList command = cardStr.split(";");
    for(int i=1;i<=7;i++){
        if(command[i]==selectedCard)
        {
            command[i] = "selected_card";
            break;
        }
    }
    cardStr = command.join(";");
}

void Game::gameOver()
{
    QFile historyFile("gamehistiory.json");
    QJsonObject records,newRecord;
    if (historyFile.open(QIODevice::ReadOnly)) {
        QByteArray data = historyFile.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        records = doc.object();
        historyFile.close();
    }
    QString winnerName;
    for(int i=0;i<4;i++){
        newRecord[gamers[i]->getUserName()] = QString::number(gamers[i]->gettStatusRound(0)) + ";" + QString::number(gamers[i]->gettStatusRound(1)) + ";"+ QString::number(gamers[i]->gettStatusRound(2));
        if(gamers[i]->numOfWins()>=2){
            winnerName += gamers[i]->getUserName() + ";";
        }
    }
    newRecord["winner"] = winnerName;
    QDateTime current = QDateTime::currentDateTime();
    newRecord["data"] = current.toString();
    records.insert(QString::number(records.size()),newRecord);
    if (historyFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QJsonDocument updatedDoc(records);
        historyFile.write(updatedDoc.toJson(QJsonDocument::Indented));
        historyFile.close();
    }
    gamerCount = 0;
    round = 0;
    turn = 0;
    hand = 0;
    handPart = 0;
    removedCardsNum = 0;
    roundOverRecived = 0;
    gamers.clear();
    randomSelectionCount.clear();
    stopUsageCount.clear();
    gamers.clear();
}



void Game::gameManager()
{
    if(hand == 1 && handPart == 0)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0,3);
        turn = distrib(gen);//
    }

    if(hand!=6){
        sendToGamer(gamers[turn]->getID(),cardStr.toUtf8());//agar natoonest benevise chi?
        if(handPart==3){
            hand++;
            makeNewCardStr();
        }
        handPart++;
        handPart=handPart % 4;
        turn++;
        turn = turn%4;
        return;
    }
    else if(hand == 6){
        qDebug()<<"hand complete";
        roudOver();
        if(round == 4){
            gameOver();
            return;
        }
        makeNewCardStr();
    }
}

void Game::handleDataReceived(qintptr socketDescriptor,QString commandStr)
{
    QStringList command = commandStr.split(";");
    if(command[0].toInt() == 6)
    {
        addGamer(socketDescriptor,command[1]);
        return;
    }
    else if(command[0].toInt() == 7)
    {
        for(int i=0;i<gamerCount;i++)
        {
            if(gamers[i]->getUserName() == command[1]){
                gamers[i]->addCard(Card(command[2]));
                break;
            }
        }
        updateCardStr(command[2]);
        gameManager();
    }
    else if(command[0].toInt() == 20)
    {
        readyGamers++;
        if(readyGamers == 4){
            startGame();
        }
        return;
    }
    else if(command[0].toInt() == 19)
    {
        remGamer(command[1]);
        return;
    }
    else if(command[0].toInt() == 10)
    {
        for(int i=0;i<gamers.size();i++)
        {
            if(gamers[i]->getUserName() != command[1])
            {
                sendToGamer(gamers[i]->getID(),commandStr);
            }

        }
        return;
    }
    else if(command[0].toInt() == 8)
    {
        if(command.size() >= 2) {
            QString username = command[1];
            randomSelectionCount[username]++;
            qDebug() << "Random selection count for" << username << ":" << randomSelectionCount[username];
            if(randomSelectionCount[username] > 3) {
                qDebug() << "User" << username << "exceeded random selection limit";
                gameOverRandom();
                return;
            }
        }
    }

    else if(command[0].toInt() == 9)
    {
        if(command.size() >= 2) {
            QString username = command[1];
            stopUsageCount[username]++;
            qDebug() << "Stop usage detected for user:" << username;
            gameOverStop();
            return;
        }
    }
    else if(command[18].toInt() == 18)
    {
        roundOverRecived++;
        if(roundOverRecived == gamerCount){
            roundOverRecived=0;
            gameManager();
        }
    }
    else
    {
        qDebug()<<"HOSHDAR "<<commandStr;
    }


}

void Game::newGamerAddedSlot()
{
    if(gamerCount < 4){
        QString data = "count;" + QString::number(gamerCount);
        for(int i=0;i<gamers.size();i++)
        {
            sendToGamer(gamers[i]->getID(),data);
        }
        return;
    }
    else if(gamerCount == 4)
    {
        QString data = "start;0";
        for(int i=0;i<gamers.size();i++)
        {
            sendToGamer(gamers[i]->getID(),data);
        }
        return;
    }
}

void Game::roudOver()
{
    if (allGamersHaveCompleteHands()) {
        qDebug()<<"round "<<round<<" over";
        evaluateAllHands();
        qDebug()<<"all hands evaluate";
        Gamer* winner = determineRoundWinner();
        qDebug()<<"round winner determine";
        sendRoundResults(winner);
        for (int i=0;i<gamers.size();i++)
        {
            gamers[i]->clearHand();
        }
        round++;
        hand = 1;
        handPart = 0;
        removedCardsNum = 0;
        roundOverRecived = 0;
        shuffle(cards);
    }
}

void Game::evaluateAllHands()
{
    for (int i=0;i<gamers.size();i++)
    {
        if (gamers[i]->hasCompleteHand()) {
            QVector<Card> hand = gamers[i]->getHand();
            auto pattern = m_handEvaluator->evaluate(hand);
            gamers[i]->setHandPattern(std::move(pattern));
            qDebug()<<gamers[i]->getHandPattern()->getName()<<" set for "<<gamers[i]->getUserName();
        }
    }
}

Gamer* Game::determineRoundWinner()
{
    if (gamers.isEmpty()) return nullptr;
    int indexWinner=0;
    Gamer* winner = gamers[0];

    for (int i = 1; i < gamers.size(); ++i) {
        const HandPattern* currentPattern = gamers[i]->getHandPattern();
        const HandPattern* winnerPattern = winner->getHandPattern();

        if (!currentPattern || !winnerPattern) continue;

        int currentStrength = currentPattern->getStrength();
        int winnerStrength = winnerPattern->getStrength();

        if (currentStrength > winnerStrength) {
            winner = gamers[i];
            indexWinner = i;
        }
        else if (currentStrength == winnerStrength) {
            QVector<Card> currentCards = currentPattern->getCards();
            QVector<Card> winnerCards = winnerPattern->getCards();

            for (int j = 0; j < qMin(currentCards.size(), winnerCards.size()); ++j) {
                if (currentCards[j].getRankValue() > winnerCards[j].getRankValue()) {
                    winner = gamers[i];
                    indexWinner = i;
                    break;
                } else if (currentCards[j].getRankValue() < winnerCards[j].getRankValue()) {
                    break;
                }
            }
        }
    }
    for(int i=0;i<gamerCount;i++)
    {
        if(i == indexWinner)
        {
            gamers[i]->setStatusRound(round-1,1);
        }
        else
        {
            gamers[i]->setStatusRound(round-1,0);
        }
    }
    winnerRound[round-1] = indexWinner;
    return winner;
}

void Game::sendRoundResults(Gamer* winner)
{
    QString resultData = "round_over;";
    for (int i=0;i<gamers.size();i++)
    {
        resultData += gamers[i]->getUserName() + ";" + gamers[i]->getHandPattern()->getName() + ";";
    }
    resultData += winner->getUserName();
    for (int i=0;i<gamers.size();i++)
    {
        sendToGamer(gamers[i]->getID(), resultData);
    }
}

qintptr Game::getIdByUsername(const QString& username)
{
    for(int i = 0; i < gamers.size(); i++) {
        if(gamers[i]->getUserName() == username) {
            return gamers[i]->getID();
        }
    }
    return -1;
}

bool Game::allGamersHaveCompleteHands() const
{
    for (int i=0;i<gamers.size();i++)
    {
        if (!gamers[i]->hasCompleteHand()) {
            return false;
        }
    }
    return true;
}

void Game::gameOverRandom()
{
    qDebug() << "Game Over Random - Too many random selections detected";

    QString violatingUser;
    for(auto it = randomSelectionCount.begin(); it != randomSelectionCount.end(); ++it) {
        if(it.value() > 2) {
            violatingUser = it.key();
            break;
        }
    }

    for(int i = 0; i < gamers.size(); i++) {
        QString username = gamers[i]->getUserName();
        qintptr userId = gamers[i]->getID();

        if(username == violatingUser) {
            sendToGamer(userId, "finishgame;-1");
            qDebug() << "Sent finishgame;-1 to violating user:" << username;
        } else {
            sendToGamer(userId, "finishgame;0");
            qDebug() << "Sent finishgame;0 to user:" << username;
        }
    }

    gamerCount = 0;
    round = 0;
    turn = 0;
    hand = 0;
    handPart = 0;
    removedCardsNum = 0;
    randomSelectionCount.clear();
    gamers.clear();

    qDebug() << "Game terminated due to excessive random selections";
}

void Game::gameOverStop()
{
    qDebug() << "Game Over Stop - Excessive stop usage detected";
    QString stoppingUser;
    for(auto it = stopUsageCount.begin(); it != stopUsageCount.end(); ++it) {
        if(it.value() > 0) {
            stoppingUser = it.key();
            break;
        }
    }
    for(int i = 0; i < gamers.size(); i++) {
        QString username = gamers[i]->getUserName();
        qintptr userId = gamers[i]->getID();

        if(username == stoppingUser) {
            sendToGamer(userId, "finishgame;0");
            qDebug() << "Sent finishgame;0 to stopping user:" << username;
        } else {
            sendToGamer(userId, "finishgame;-1");
            qDebug() << "Sent finishgame;-1 to user:" << username;
        }
    }
    gamerCount = 0;
    round = 0;
    turn = 0;
    hand = 0;
    handPart = 0;
    removedCardsNum = 0;
    randomSelectionCount.clear();
    stopUsageCount.clear();
    gamers.clear();
    qDebug() << "Game terminated due to stop usage";
}
