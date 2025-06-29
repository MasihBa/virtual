// myserver.cpp

#include "myserver.h"
#include "mythread.h"

MyServer::MyServer(QObject *parent) :
    QTcpServer(parent)
{
    lock = new QMutex();
}
void MyServer::startServer(int _port)
{
    int port = _port;

    if(!this->listen(QHostAddress::Any,port))
    {
        qDebug() << "Could not start server ! ";
    }
    else
    {
        qDebug() << "Listening to port : " << port << "...";
    }
}

void MyServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << socketDescriptor << " Connecting...";
    MyThread *thread = new MyThread(socketDescriptor, this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}
