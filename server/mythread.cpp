#include "mythread.h"
#include <QString>
#include <QStringList>

MyThread::MyThread(qintptr ID,QMutex* _lock,QObject *parent) :
    QThread(parent)
{
    lock = _lock;
    socketDescriptor = ID;
}
void MyThread::run()
{
    qDebug() << " Thread started";
    socket = new QTcpSocket();
    if(!socket->setSocketDescriptor(this->socketDescriptor))
    {
        emit error(socket->error());
        return;
    }
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()) , Qt::DirectConnection );
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    qDebug() << socketDescriptor << " Client connected";
    exec();
}

void MyThread::readyRead()
{
    QString commandStr = socket->readAll();
    QStringList command = commandStr.split(";");
    if(command[0].toInt() == 1)
    {
        QMutexLocker locker(lock);
        QString data;
        data = signUp.registeration(command[1],command[2],command[3],command[4],command[5],command[6]);
        socket->write(data.toUtf8());

    }
    else if(command[0].toInt() == 2)
    {
        QMutexLocker locker(lock);
        QString data;
        data = signIn.check(command[1],command[2]);
        socket->write(data.toUtf8());
    }
    else if(command[0].toInt() == 3)
    {
        QMutexLocker locker(lock);
        QString data;
        data = recovery.check(command[1],command[2]);
        socket->write(data.toUtf8());
    }
    else if(command[0].toInt() == 4)
    {
        QMutexLocker locker(lock);
        QString data;
        data = getInfo.getInfo(command[1]);
        socket->write(data.toUtf8());
    }
    else if(command[0].toInt() == 5)
    {
        QMutexLocker locker(lock);
        QString data;
        data = update.updateInfo(command[1],command[2],command[3],command[4],command[5],command[6]);
        socket->write(data.toUtf8());
    }
    else if(command[0].toInt() == 6)
    {
        emit dataReceived(socketDescriptor,commandStr);
    }
    socket->waitForBytesWritten(-1);
}

void MyThread::disconnected()
{
    qDebug() << socketDescriptor << " Disconnected";
    socket->deleteLater();
    exit(0);
}

void MyThread::writeToSocket(const QByteArray &data)
{
    socket->write(data);
    socket->waitForBytesWritten(-1);
}
