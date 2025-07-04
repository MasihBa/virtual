#include "handevaluator.h"
#include "handutils.h"

#include "goldenhand.h"
#include "orderhand.h"
#include "fourrank.h"
#include "penthouse.h"
#include "mschand.h"
#include "series.h"
#include "threekind.h"
#include "doublepair.h"
#include "singlepair.h"
#include "messyhand.h"

HandEvaluator::HandEvaluator() {
    m_patterns.push_back(std::make_unique<GoldenHand>());
    m_patterns.push_back(std::make_unique<OrderHand>());
    m_patterns.push_back(std::make_unique<Fourrank>());
    m_patterns.push_back(std::make_unique<Penthouse>());
    m_patterns.push_back(std::make_unique<MscHand>());
    m_patterns.push_back(std::make_unique<Series>());
    m_patterns.push_back(std::make_unique<ThreeOfAKind>());
    m_patterns.push_back(std::make_unique<DoublePair>());
    m_patterns.push_back(std::make_unique<SinglePair>());
    m_patterns.push_back(std::make_unique<MessyHand>());
}

//std::unique_ptr<HandPattern> HandEvaluator::evaluate(QVector<Card> hand) {
    std::unique_ptr<HandPattern> HandEvaluator::evaluate(const QVector<Card>& hand) {
    if (hand.size() != 5) {
        return nullptr;
    }

     QVector<Card> sortedHand = hand;
    HandUtils::sortHandDescending(sortedHand);

    for (const auto& patternPrototype : m_patterns) {
        auto result = patternPrototype->evaluate(hand);
        if (result != nullptr) {
            return result;
        }
    }

    return nullptr;
}
