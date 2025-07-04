#ifndef MESSYHAND_H
#define MESSYHAND_H

#include "handpattern.h"

class MessyHand : public HandPattern {
public:
    MessyHand() = default;
    MessyHand(const QVector<Card>& cards);

    int getStrength() const override { return 1; }
    QString getName() const override { return "Hand Messy"; }
    std::unique_ptr<HandPattern> evaluate(const QVector<Card>& sortedHand) const override;
    int compare(const HandPattern& other) const override;
};

#endif // MESSYHAND_H
