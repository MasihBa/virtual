#include "orderhand.h"
#include "handutils.h"

OrderHand::OrderHand(const QVector<Card>& cards) {
    m_cards = cards;
}

std::unique_ptr<HandPattern> OrderHand::evaluate(const QVector<Card>& sortedHand) const {
    if (sortedHand.size() != 5) {
        return nullptr;
    }

    if (!HandUtils::isFlush(sortedHand)) {
        return nullptr;
    }

    if (isConsecutive(sortedHand)) {
        if (sortedHand[0].getRank() == Card::Rank::Bitcoin &&
            sortedHand[1].getRank() == Card::Rank::King &&
            sortedHand[2].getRank() == Card::Rank::Queen &&
            sortedHand[3].getRank() == Card::Rank::Soldior &&
            sortedHand[4].getRank() == Card::Rank::Rank10) {
            return nullptr;
        }

        return std::make_unique<OrderHand>(sortedHand);
    }

    return nullptr;
}

int OrderHand::compare(const HandPattern& other) const {
    const auto& otherHand = dynamic_cast<const OrderHand&>(other);

    if (m_cards[0].getRankValue() > otherHand.m_cards[0].getRankValue()) {
        return 1;
    }
    if (m_cards[0].getRankValue() < otherHand.m_cards[0].getRankValue()) {
        return -1;
    }

    if (m_cards[0].getUnitValue() > otherHand.m_cards[0].getUnitValue()) {
        return 1;
    }
    if (m_cards[0].getUnitValue() < otherHand.m_cards[0].getUnitValue()) {
        return -1;
    }

    return 0;
}

bool OrderHand::isConsecutive(const QVector<Card>& hand) const {
    for (int i = 0; i < 4; ++i) {
        if (hand[i].getRankValue() != hand[i+1].getRankValue() + 1) {
            return false;
        }
    }
    return true;
}
