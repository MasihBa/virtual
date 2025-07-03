// singlepair.h
#ifndef SINGLEPAIR_H
#define SINGLEPAIR_H

#include "handpattern.h"
#include <QVector>
#include "card.h"

class SinglePair : public HandPattern {
public:
    SinglePair() = default;
    explicit SinglePair(const QVector<Card>& cards);
    int getStrength() const override;
    QString getName() const override;
    int compare(const HandPattern& other) const override;
    std::unique_ptr<HandPattern> evaluate(const QVector<Card>& sortedHand) const override;

private:

    int m_pairRankValue;
    int m_kicker1Value;
    int m_kicker2Value;
    int m_kicker3Value;
};

#endif // SINGLEPAIR_H
