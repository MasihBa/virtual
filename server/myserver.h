#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include <QMutex>
#include "mythread.h"

class MyServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyServer(QObject *parent = nullptr);
    void startServer(int _port);
signals:

public slots:

protected:
    void incomingConnection(qintptr socketDescriptor);
    QMutex* lock;

};

#endif // MYSERVER_H

