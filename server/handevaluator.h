#ifndef HANDEVALUATOR_H
#define HANDEVALUATOR_H

// #include "handpattern.h"
// #include "card.h"
// #include <QVector>
// #include <memory>

// class HandEvaluator {
// public:
//     HandEvaluator();
//     // std::unique_ptr<HandPattern> evaluateHand(QVector<Card> hand);
//     std::unique_ptr<HandPattern> evaluate(const QVector<Card>& hand);
// private:
//     QVector<std::unique_ptr<HandPattern>> m_patterns;
// };

// #endif // HANDEVALUATOR_H


#include "handpattern.h"
#include "card.h"
#include <vector>
#include <memory>
#include <QVector>

class HandEvaluator {
public:
    HandEvaluator();
    std::unique_ptr<HandPattern> evaluate(const QVector<Card>& hand);

private:
    std::vector<std::unique_ptr<HandPattern>> m_patterns;
};

#endif
