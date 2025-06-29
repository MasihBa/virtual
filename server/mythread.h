#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include "signin.h"
#include "signup.h"
#include "changeinfo.h"
#include <QMutex>
class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(qintptr ID, QObject *parent = nullptr,QMutex* _lock);

    void run();

signals:
    void error(QTcpSocket::SocketError socketerror);

public slots:
    void readyRead();
    void disconnected();

private:
    QMutex* lock;
    QTcpSocket *socket;
    signin signIn;
    signup signUp;
    ChangeInfo update;
    qintptr socketDescriptor;
};

#endif
