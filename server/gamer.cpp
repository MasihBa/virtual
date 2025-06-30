#include "gamer.h"

Gamer::Gamer(qintptr id, MyThread* _thread, QString _username,QObject *parent)
    : QObject{parent}
{
    ID = id;
    thread = _thread;
    username = _username;
    statusInRound[0] = 0;
    statusInRound[1] = 0;
    statusInRound[2] = 0;
}

int Gamer::numOfWins()
{
    return statusInRound[0]+statusInRound[1]+statusInRound[2];
}

void Gamer::addCard(const Card &_card)
{
    hand.push_back(_card);
}
