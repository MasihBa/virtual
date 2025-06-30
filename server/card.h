#ifndef CARD_H
#define CARD_H

#include <QString>

class Card
{
public:


    Card(const QString &cardString);
    Card(int unitIndex, int rankIndex);
    Card(const Card &other);
    Card &operator=(const Card &other);

    QString toString() const;

private:

    enum Unit {
        Diamond,
        Coin,
        Dollar,
        Gold
    };

    enum Rank {
        Rank2,
        Rank3,
        Rank4,
        Rank5,
        Rank6,
        Rank7,
        Rank8,
        Rank9,
        Rank10,
        Soldior,
        Queen,
        King,
        Bitcoin
    };

    Unit m_unit;
    Rank m_rank;

    static Unit stringToUnit(const QString &str);
    static Rank stringToRank(const QString &str);
    static QString unitToString(Unit unit);
    static QString rankToString(Rank rank);
};

#endif // CARD_H

