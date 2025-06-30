// myserver.cpp

#include "myserver.h"
#include "mythread.h"

MyServer::MyServer(QObject *parent) :
    QTcpServer(parent)
{
    lock = new QMutex();
    gameController = new Game();
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
    MyThread *thread = new MyThread(socketDescriptor,lock,this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(thread,SIGNAL(dataReceived(qintptr,QString)),gameController,SLOT(handleDataReceived(qintptr,QString)));
    gameController->addNewOnlineUser(socketDescriptor, thread);
    thread->start();
}

MyServer::~MyServer(){
    delete lock;
    delete gameController;
}
