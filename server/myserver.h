#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include <QMutex>
#include "mythread.h"
#include "game.h"
#include <QMap>

class MyServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyServer(QObject *parent = nullptr);
    ~MyServer();
    int startServer(int _port);
protected:
    void incomingConnection(qintptr socketDescriptor);
private:
    QMutex* lock;
    Game* gameController;


};

#endif // MYSERVER_H

