#ifndef FOUROFAKIND_H
#define FOUROFAKIND_H

#include "handpattern.h"

class FourOfAKind : public HandPattern {
public:
    FourOfAKind() = default;
    FourOfAKind(const QVector<Card>& cards);

    int getStrength() const override { return 8; }
    QString getName() const override { return "Hand 4+1"; }
    std::unique_ptr<HandPattern> evaluate(const QVector<Card>& sortedHand) const override;
    int compare(const HandPattern& other) const override;

private:
    Card::Rank getFourRank() const;
};

#endif // FOUROFAKIND_H
