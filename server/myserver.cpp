// myserver.cpp

#include "myserver.h"
#include "mythread.h"

MyServer::MyServer(QObject *parent) :
    QTcpServer(parent)
{
    lock = new QMutex();
    gameController = new Game();
}
int MyServer::startServer(int _port)
{
    int port = _port;

    if(!this->listen(QHostAddress::Any,port))
    {
        qDebug() << "Could not start server ! ";
        return 0;
    }
    else
    {
        qDebug() << "Listening to port : " << port << "...";
        return 1;
    }
}

void MyServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << socketDescriptor << " Connecting...";
    MyThread *thread = new MyThread(socketDescriptor,lock,this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(thread,SIGNAL(dataReceived(qintptr,QString)),gameController,SLOT(handleDataReceived(qintptr,QString)));
    connect(thread,&MyThread::connected,gameController,&Game::addNewOnlineUser);
    thread->start();
}

MyServer::~MyServer(){
    delete lock;
    delete gameController;
}
