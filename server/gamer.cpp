#include "gamer.h"

Gamer::Gamer(qintptr id, QString _username,QObject *parent)
    : QObject{parent}
{
    ID = id;
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


void Gamer::setHandPattern(std::unique_ptr<HandPattern> pattern)
{
    m_handPattern = std::move(pattern);
}

const HandPattern* Gamer::getHandPattern() const
{
    return m_handPattern.get();
}

void Gamer::clearHand()
{
    hand.clear();
    m_handPattern.reset();
}

void Gamer::addRoundWin(int roundIdx) {
    if (roundIdx >= 0 && roundIdx < 3)
        statusInRound[roundIdx] = 1;
}

int Gamer::getRoundWins() const {
    return statusInRound[0] + statusInRound[1] + statusInRound[2];
}
