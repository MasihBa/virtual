#include "fourrank.h"
#include "handutils.h"

Fourrank::Fourrank(const QVector<Card>& cards) {
    m_cards = cards;
}

std::unique_ptr<HandPattern> Fourrank::evaluate(const QVector<Card>& sortedHand) const {
    if (sortedHand.size() != 5) {
        return nullptr;
    }

    QMap<Card::Rank, int> rankCounts = HandUtils::getRankCounts(sortedHand);

    bool hasFourOfAKind = false;
    bool hasKicker = false;

    for (auto it = rankCounts.begin(); it != rankCounts.end(); ++it) {
        if (it.value() == 4) {
            hasFourOfAKind = true;
        } else if (it.value() == 1) {
            hasKicker = true;
        }
    }

    if (hasFourOfAKind && hasKicker && rankCounts.size() == 2) {
        return std::make_unique<Fourrank>(sortedHand);
    }

    return nullptr;
}

int Fourrank::compare(const HandPattern& other) const {
    const auto& otherHand = dynamic_cast<const Fourrank&>(other);

    Card::Rank myFourRank = getFourRank();
    Card::Rank otherFourRank = otherHand.getFourRank();
    int myFourValue = static_cast<int>(myFourRank);
    int otherFourValue = static_cast<int>(otherFourRank);
    if (myFourValue > otherFourValue) {
        return 1;
    }
    if (myFourValue < otherFourValue) {
        return -1;
    }

    return 0;
}

Card::Rank Fourrank::getFourRank() const {
    QMap<Card::Rank, int> rankCounts = HandUtils::getRankCounts(m_cards);
    for (auto it = rankCounts.begin(); it != rankCounts.end(); ++it) {
        if (it.value() == 4) {
            return it.key();
        }
    }
    return Card::Rank::Rank2; // default value
}
