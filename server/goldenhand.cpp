#include "goldenhand.h"
#include "handutils.h"

GoldenHand::GoldenHand(const QVector<Card>& cards) {
    m_cards = cards;
}

std::unique_ptr<HandPattern> GoldenHand::evaluate(const QVector<Card>& sortedHand) const {
    if (sortedHand.size() == 5 && HandUtils::isFlush(sortedHand) &&
        sortedHand[0].getRank() == Card::Rank::Bitcoin &&
        sortedHand[1].getRank() == Card::Rank::King &&
        sortedHand[2].getRank() == Card::Rank::Queen &&
        sortedHand[3].getRank() == Card::Rank::Soldier &&
        sortedHand[4].getRank() == Card::Rank::Rank10) {
        return std::make_unique<GoldenHand>(sortedHand);
    }
    return nullptr;
}

int GoldenHand::compare(const HandPattern& other) const {
    const auto& otherHand = dynamic_cast<const GoldenHand&>(other);
    if (m_cards[0].getUnitValue() > otherHand.m_cards[0].getUnitValue()) return 1;
    if (m_cards[0].getUnitValue() < otherHand.m_cards[0].getUnitValue()) return -1;
    return 0;
}
