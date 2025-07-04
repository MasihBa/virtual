#include "messyhand.h"

MessyHand::MessyHand(const QVector<Card>& cards) {
    m_cards = cards;
}

std::unique_ptr<HandPattern> MessyHand::evaluate(const QVector<Card>& sortedHand) const {
    return std::make_unique<MessyHand>(sortedHand);
}

int MessyHand::compare(const HandPattern& other) const {
    const auto& otherHand = dynamic_cast<const MessyHand&>(other);
    for (int i = 0; i < m_cards.size(); ++i) {
        if (m_cards[i].getRankValue() > otherHand.m_cards[i].getRankValue()) return 1;
        if (m_cards[i].getRankValue() < otherHand.m_cards[i].getRankValue()) return -1;
    }
    for (int i = 0; i < m_cards.size(); ++i) {
        if (m_cards[i].getUnitValue() > otherHand.m_cards[i].getUnitValue()) return 1;
        if (m_cards[i].getUnitValue() < otherHand.m_cards[i].getUnitValue()) return -1;
    }
    return 0;
}
