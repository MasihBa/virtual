#ifndef ORDERHAND_H
#define ORDERHAND_H

#include "handpattern.h"

class OrderHand : public HandPattern {
public:
    OrderHand() = default;
    OrderHand(const QVector<Card>& cards);

    int getStrength() const override { return 9; }
    QString getName() const override { return "Hand Order"; }
    std::unique_ptr<HandPattern> evaluate(const QVector<Card>& sortedHand) const override;
    int compare(const HandPattern& other) const override;

private:
    bool isConsecutive(const QVector<Card>& hand) const;
};

#endif // ORDERHAND_H
