#ifndef GAME_H
#define GAME_H

#include <QVector>
#include <QMap>
#include "mythread.h"
#include "gamer.h"

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(QObject *parent = nullptr);
    void addGamer(qintptr id,MyThread* client,QString username);
    void addNewOnlineUser(qintptr id,MyThread* thread);
    int getGamerCount() const {return gamerCount;}
    void sendToGamer(MyThread* user,const QString& data);

signals:
    void newGamerAdded();
private:
    int gamerCount;
    QVector<Gamer*> gamers;
    QMap<qintptr,MyThread*> onlineUsers;

public slots:
    void handleDataReceived(qintptr socketDescriptor, const QString &commandStr);
    void newGamerAddedSlot();
};

#endif // GAME_H
