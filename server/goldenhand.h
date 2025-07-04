#ifndef GOLDENHAND_H
#define GOLDENHAND_H

#include "handpattern.h"

class GoldenHand : public HandPattern {
public:
    GoldenHand() = default;
    GoldenHand(const QVector<Card>& cards);

    int getStrength() const override { return 10; }
    QString getName() const override { return "Hand Golden"; }
    std::unique_ptr<HandPattern> evaluate(const QVector<Card>& sortedHand) const override;
    int compare(const HandPattern& other) const override;
};

#endif // GOLDENHAND_H
