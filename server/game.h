#ifndef GAME_H
#define GAME_H

#include <QVector>
#include <QMap>
#include "mythread.h"
#include "gamer.h"
#include "card.h"
#include "handevaluator.h"

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(QObject *parent = nullptr);
    void addGamer(qintptr id,QString username);
    int getGamerCount() const {return gamerCount;}
    void sendToGamer(qintptr _id,const QString& data);
    void startGame();
    void shuffle(QVector<Card>& _cards);
    void gameManager();
    void roudOver();
    void makeNewCardStr();
    void updateCardStr(QString& selectedCard);
    void gameOver();
    void evaluateAllHands();
    Gamer* determineRoundWinner();
    void sendRoundResults(Gamer* winner);
    bool allGamersHaveCompleteHands() const;
signals:
    void newGamerAdded();

private:
    int gamerCount;
    int readyGamers;
    int round;
    int turn;
    int hand;
    int handPart;
    int removedCardsNum;
    int winnerRound[3];
    QString cardStr;
    QVector<Card> cards;
    QVector<Gamer*> gamers;
    QMap<qintptr,MyThread*> _onlineUsers;
    std::unique_ptr<HandEvaluator> m_handEvaluator;

public slots:
    void handleDataReceived(qintptr socketDescriptor,QString commandStr);
    void addNewOnlineUser(qintptr id,MyThread* thread);
    void newGamerAddedSlot();
};

#endif // GAME_H
