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
    void startServer(int _port);
signals:

public slots:

protected:
    void incomingConnection(qintptr socketDescriptor);
    QMutex* lock;
    Game* gameController;

};

#endif // MYSERVER_H

