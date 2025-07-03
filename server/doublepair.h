// doublepair.h
#ifndef DOUBLEPAIR_H
#define DOUBLEPAIR_H

#include "handpattern.h"

class DoublePair : public HandPattern {
public:
    DoublePair() = default;
    explicit DoublePair(const QVector<Card>& cards);

    int getStrength() const override;
    QString getName() const override;
    std::unique_ptr<HandPattern> evaluate(const QVector<Card>& sortedHand) const override;
    int compare(const HandPattern& other) const override;

private:
    int m_highPairRankValue = 0;
    int m_lowPairRankValue = 0;
    int m_kickerRankValue = 0;
};

#endif // DOUBLEPAIR_H
