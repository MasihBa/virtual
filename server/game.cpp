#include "game.h"

Game::Game(QObject *parent)
    : QObject{parent}
{
    gamerCount = 0;
    connect(this,SIGNAL(newGamerAdded()),this,SLOT(newGamerAddedSlot()));
}

void Game::addGamer(qintptr id, MyThread *client, QString username)
{
    gamers.push_back(new Gamer(id,client,username));
    gamerCount++;
    emit newGamerAdded();
}

void Game::addNewOnlineUser(qintptr id, MyThread *thread)
{
    onlineUsers.insert(id,thread);
}

void Game::sendToGamer(MyThread *user, const QString &data)
{
    QMetaObject::invokeMethod(user, "writeToSocket", Qt::QueuedConnection, Q_ARG(QByteArray, data.toUtf8()));
}

void Game::handleDataReceived(qintptr socketDescriptor, const QString &commandStr)
{
    QStringList command = commandStr.split(";");
    if(command[0].toInt() == 6)
    {
        addGamer(socketDescriptor,onlineUsers[socketDescriptor],command[1]);
    }
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
    }
}



