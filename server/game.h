#ifndef GAME_H
#define GAME_H

#include <QVector>
#include <QMap>
#include "mythread.h"
#include "gamer.h"
#include "card.h"

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(QObject *parent = nullptr);
    void addGamer(qintptr id,MyThread* client,QString username);
    void addNewOnlineUser(qintptr id,MyThread* thread);
    int getGamerCount() const {return gamerCount;}
    void sendToGamer(MyThread* user,const QString& data);
    void startGame();
    void shuffle(QVector<Card>& _cards);
    void gameManager();
    void roudOver();
    void makeNewCardStr();
    void updateCardStr(QString& selectedCard);
    void gameOver();

signals:
    void newGamerAdded();

private:
    int gamerCount;
    int round;
    int turn;
    int hand;
    int handPart;
    int removedCardsNum;
    QString cardStr;
    QVector<Card> cards;
    QVector<Gamer*> gamers;
    QMap<qintptr,MyThread*> _onlineUsers;

public slots:
    void handleDataReceived(qintptr socketDescriptor, const QString &commandStr);
    void newGamerAddedSlot();
};

#endif // GAME_H
