#ifndef HANDPATTERN_H
#define HANDPATTERN_H

#include "card.h"
#include <QVector>
#include <QString>
#include <memory>

class HandPattern {
public:
    virtual ~HandPattern() = default;
    virtual int getStrength() const = 0;
    virtual QString getName() const = 0;
    virtual std::unique_ptr<HandPattern> evaluate(const QVector<Card>& sortedHand) const = 0;
    virtual int compare(const HandPattern& other) const = 0;
    const QVector<Card>& getCards() const { return m_cards; }

protected:
    QVector<Card> m_cards;
};

#endif // HANDPATTERN_H
