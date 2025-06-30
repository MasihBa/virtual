#include "game.h"
#include <algorithm>
#include <random>

Game::Game(QObject *parent)
    : QObject{parent}
{
    gamerCount = 0;
    round = 0;
    hand = 0;
    handPart = 0;
    removedCardsNum = 0;
    connect(this,SIGNAL(newGamerAdded()),this,SLOT(newGamerAddedSlot()));
    for(int i=1; i<=4 ; i++){
        for(int j=1; j<=13 ;j++){
            cards.push_back(Card(i,j));
        }
    }
}

void Game::addGamer(qintptr id, MyThread *client, QString username)
{
    gamers.push_back(new Gamer(id,client,username));
    gamerCount++;
    emit newGamerAdded();
}

void Game::addNewOnlineUser(qintptr id, MyThread *thread)
{
    _onlineUsers.insert(id,thread);
}

void Game::sendToGamer(MyThread *user, const QString &data)
{
    QMetaObject::invokeMethod(user, "writeToSocket", Qt::QueuedConnection, Q_ARG(QByteArray, data.toUtf8()));
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

void Game::updateCardStr(QString &selectedCard)
{
    QStringList command = cardStr.split(";");
    for(int i=1;i<7;i++){
        if(command[i]==selectedCard)
        {
            command[i] = "card_selected";
            break;
        }
    }
    cardStr = command.join(";");
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

    if(hand!=5){
        sendToGamer(gamers[turn]->getThread(),cardStr.toUtf8());//agar natoonest benevise chi?
        if(handPart==3){
            hand++;
            makeNewCardStr();
        }
        handPart++;
        handPart=handPart % 4;
        turn++;
        turn = turn%4;
    }
    else if(hand == 6){
        hand = 1;
        handPart = 0;
        removedCardsNum = 0;
        shuffle(cards);
        //?????????
    }
    if(round == 4){
        //????????
    }
}

void Game::handleDataReceived(qintptr socketDescriptor, const QString &commandStr)
{
    QStringList command = commandStr.split(";");
    if(command[0].toInt() == 6)
    {
        addGamer(socketDescriptor,_onlineUsers[socketDescriptor],command[1]);
    }
    else if(command[0].toInt() == 7)
    {
        for(int i=0;i<4;i++)
        {
            if(gamers[i]->getUserName() == command[1]){
                gamers[i]->addCard(Card(command[2]));
                break;
            }
        }
        updateCardStr(command[2]);
    }
    gameManager();
}

void Game::newGamerAddedSlot()
{
    if(gamerCount < 4){
        QString data = "count;" + QString::number(gamerCount);
        for(int i=0;i<gamers.size();i++)
        {
            sendToGamer(gamers[i]->getThread(),data);
        }
    }
    else if(gamerCount == 4)
    {
        QString data = "start;0";
        for(int i=0;i<gamers.size();i++)
        {
            sendToGamer(gamers[i]->getThread(),data);
        }
        startGame();
    }
}



