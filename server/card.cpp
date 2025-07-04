#include "card.h"
#include <QStringList>
#include <stdexcept>

Card::Card(int unitIndex, int rankIndex)
{
    m_unit = static_cast<Unit>(unitIndex);
    m_rank = static_cast<Rank>(rankIndex);
}

Card::Card(const QString &cardString)
{
    QStringList parts = cardString.split("-");
    m_unit = stringToUnit(parts[0]);
    m_rank = stringToRank(parts[1]);
}

Card::Card(const Card &other)
{
    m_unit = other.m_unit;
    m_rank = other.m_rank;
}

Card &Card::operator=(const Card &other)
{
    if (this != &other) {
        m_unit = other.m_unit;
        m_rank = other.m_rank;
    }
    return *this;
}

QString Card::toString() const
{
    return unitToString(m_unit) + "-" + rankToString(m_rank);
}
Card::Unit Card::getUnit() const {
    return m_unit;
}

Card::Rank Card::getRank() const {
    return m_rank;
}
int Card::getUnitValue() const {
    switch (m_unit) {
    case Diamond: return 4;
    case Gold:    return 3;
    case Dollar:  return 2;
    case Coin:    return 1;
    }
    return 0;
}

int Card::getRankValue() const {
    return static_cast<int>(m_rank);
}

bool Card::operator<(const Card& other) const {
    int thisRankValue = this->getRankValue();
    int otherRankValue = other.getRankValue();

    if (thisRankValue < otherRankValue) {
        return true;
    }
    if (thisRankValue > otherRankValue) {
        return false;
    }
    return this->getUnitValue() < other.getUnitValue();
}

Card::Unit Card::stringToUnit(const QString &str)
{
    if(str == "Diamond") return Diamond;
    if(str == "Coin")    return Coin;
    if(str == "Dollar")  return Dollar;
    if(str == "Gold")    return Gold;
    return Diamond;
}

Card::Rank Card::stringToRank(const QString &str)
{
    if(str == "2")        return Rank2;
    if(str == "3")        return Rank3;
    if(str == "4")        return Rank4;
    if(str == "5")        return Rank5;
    if(str == "6")        return Rank6;
    if(str == "7")        return Rank7;
    if(str == "8")        return Rank8;
    if(str == "9")        return Rank9;
    if(str == "10")       return Rank10;
    if(str == "Soldier")  return Soldier;
    if(str == "Queen")    return Queen;
    if(str == "King")     return King;
    if(str == "Bitcoin")  return Bitcoin;
    return Rank2;
}

QString Card::unitToString(Card::Unit unit)
{
    switch(unit) {
    case Diamond: return "Diamond";
    case Coin:    return "Coin";
    case Dollar:  return "Dollar";
    case Gold:    return "Gold";
    }
    return "";
}

QString Card::rankToString(Card::Rank rank)
{
    switch(rank) {
    case Rank2:      return "2";
    case Rank3:      return "3";
    case Rank4:      return "4";
    case Rank5:      return "5";
    case Rank6:      return "6";
    case Rank7:      return "7";
    case Rank8:      return "8";
    case Rank9:      return "9";
    case Rank10:     return "10";
    case Soldier:    return "Soldier";
    case Queen:      return "Queen";
    case King:       return "King";
    case Bitcoin:    return "Bitcoin";
    }
    return "";
}
