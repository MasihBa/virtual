// threeofakind.h

#ifndef THREEOFAKIND_H
#define THREEOFAKIND_H

#include "handpattern.h"

class ThreeOfAKind : public HandPattern {
public:
    ThreeOfAKind() = default;
    explicit ThreeOfAKind(const QVector<Card>& cards);
    int getStrength() const override;
    QString getName() const override;
    std::unique_ptr<HandPattern> evaluate(const QVector<Card>& sortedHand) const override;
    int compare(const HandPattern& other) const override;

private:
    int m_threeRankValue = 0;
};

#endif // THREEOFAKIND_H
