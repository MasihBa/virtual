#ifndef GAMER_H
#define GAMER_H

#include <QObject>
#include "mythread.h"
#include <QString>
class Gamer : public QObject
{
    Q_OBJECT
public:
    explicit Gamer(qintptr id, MyThread* _thread, QString _username,QObject *parent = nullptr);
    MyThread* getThread() const {return thread;}
private:
    qintptr ID;
    MyThread* thread;
    QString username;
signals:
};

#endif // GAMER_H
