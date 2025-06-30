#include "gamer.h"

Gamer::Gamer(qintptr id, MyThread* _thread, QString _username,QObject *parent)
    : QObject{parent}
{
    ID = id;
    thread = _thread;
    username = _username;
}
