#ifndef PENTHOUSE_H
#define PENTHOUSE_H

#include "handpattern.h"

class Penthouse : public HandPattern {
public:
    Penthouse() = default;
    Penthouse(const QVector<Card>& cards);

    int getStrength() const override { return 7; }
    QString getName() const override { return "Penthouse"; }
    std::unique_ptr<HandPattern> evaluate(const QVector<Card>& sortedHand) const override;
    int compare(const HandPattern& other) const override;

private:
    Card::Rank getThreeOfAKindRank() const;
};

#endif // PENTHOUSE_H
