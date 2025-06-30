#ifndef GAMER_H
#define GAMER_H

#include <QObject>
#include "mythread.h"
#include <QString>
#include "card.h"
class Gamer : public QObject
{
    Q_OBJECT
public:
    explicit Gamer(qintptr id, MyThread* _thread, QString _username,QObject *parent = nullptr);
    MyThread* getThread() const {return thread;}
    QString getUserName() const {return username;}
    int numOfWins();
    void addCard(const Card& _card);
private:
    qintptr ID;
    MyThread* thread;
    QString username;
    QVector<Card> hand;
    int statusInRound[3];
signals:
};

#endif // GAMER_H
