#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include "signin.h"
#include "signup.h"
#include "changeinfo.h"
#include "passrecovery.h"
#include "getuserinfo.h"
#include <QMutex>

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(qintptr ID,QMutex* _lock,QObject *parent = nullptr);

    void run();

signals:
    void error(QTcpSocket::SocketError socketerror);
    void dataReceived(qintptr socketDescriptor, const QString &commandStr);

public slots:
    void readyRead();
    void disconnected();
    void writeToSocket(const QByteArray &data);

private:
    QMutex* lock;
    QTcpSocket *socket;
    signin signIn;
    signup signUp;
    ChangeInfo update;
    PassRecovery recovery;
    getUserInfo getInfo;
    qintptr socketDescriptor;
};

#endif
