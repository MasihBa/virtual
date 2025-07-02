#include "fourofkind.h"
#include "handutils.h"

FourOfAKind::FourOfAKind(const QVector<Card>& cards) {
    m_cards = cards;
}

Card::Rank FourOfAKind::getFourRank() const {
    if (m_cards[0].getRank() == m_cards[1].getRank()) {
        return m_cards[0].getRank();
    }
    return m_cards[1].getRank();
}

std::unique_ptr<HandPattern> FourOfAKind::evaluate(const QVector<Card>& sortedHand) const {
    if (sortedHand.size() != 5) return nullptr;
    auto counts = HandUtils::getRankCounts(sortedHand);
    if (counts.values().contains(4)) {
        return std::make_unique<FourOfAKind>(sortedHand);
    }
    return nullptr;
}

int FourOfAKind::compare(const HandPattern& other) const {
    const auto& otherHand = dynamic_cast<const FourOfAKind&>(other);

    int thisFourRankValue = static_cast<int>(this->getFourRank());
    int otherFourRankValue = static_cast<int>(otherHand.getFourRank());

    if (thisFourRankValue > otherFourRankValue) return 1;
    if (thisFourRankValue < otherFourRankValue) return -1;
    return 0;
}
