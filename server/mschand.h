// mschand.h

#ifndef MSCHAND_H
#define MSCHAND_H

#include "handpattern.h"

class MscHand : public HandPattern {
public:
    MscHand() = default;
    explicit MscHand(const QVector<Card>& cards);
    int getStrength() const override;
    QString getName() const override;
    std::unique_ptr<HandPattern> evaluate(const QVector<Card>& sortedHand) const override;
    int compare(const HandPattern& other) const override;
};

#endif // MSCHAND_H
