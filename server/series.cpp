// series.cpp
#include "series.h"
#include "handutils.h"

Series::Series(const QVector<Card>& cards) {
    m_cards = cards;
}

int Series::getStrength() const {
    return 5;
}

QString Series::getName() const {
    return "Series";
}

std::unique_ptr<HandPattern> Series::evaluate(const QVector<Card>& sortedHand) const {

    bool is_straight = HandUtils::isStraight(sortedHand);
    bool is_flush = HandUtils::isFlush(sortedHand);

    if (is_straight && !is_flush) {
        return std::make_unique<Series>(sortedHand);
    }

    return nullptr;
}

int Series::compare(const HandPattern& other) const {
    const auto& otherHand = dynamic_cast<const Series&>(other);
    int myHighestRankValue = m_cards[0].getRankValue();
    int otherHighestRankValue = otherHand.m_cards[0].getRankValue();

    if (myHighestRankValue > otherHighestRankValue) {
        return 1;
    }
    if (myHighestRankValue < otherHighestRankValue) {
        return -1;
    }

    return 0;
}
