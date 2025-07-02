// series.h

#ifndef SERIES_H
#define SERIES_H

#include "handpattern.h"

class Series : public HandPattern {
public:
    Series() = default;
    explicit Series(const QVector<Card>& cards);
    int getStrength() const override;
    QString getName() const override;
    std::unique_ptr<HandPattern> evaluate(const QVector<Card>& sortedHand) const override;
    int compare(const HandPattern& other) const override;
};

#endif // SERIES_H
