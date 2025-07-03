#include "penthouse.h"
#include "handutils.h"

Penthouse::Penthouse(const QVector<Card>& cards) {
    m_cards = cards;
}

std::unique_ptr<HandPattern> Penthouse::evaluate(const QVector<Card>& sortedHand) const {
    if (sortedHand.size() != 5) {
        return nullptr;
    }

    QMap<Card::Rank, int> rankCounts = HandUtils::getRankCounts(sortedHand);

    bool hasThreeOfAKind = false;
    bool hasPair = false;

    for (auto it = rankCounts.begin(); it != rankCounts.end(); ++it) {
        if (it.value() == 3) {
            hasThreeOfAKind = true;
        } else if (it.value() == 2) {
            hasPair = true;
        }
    }

    if (hasThreeOfAKind && hasPair && rankCounts.size() == 2) {
        return std::make_unique<Penthouse>(sortedHand);
    }

    return nullptr;
}

int Penthouse::compare(const HandPattern& other) const {
    const auto& otherHand = dynamic_cast<const Penthouse&>(other);
    Card::Rank myThreeRank = getThreeOfAKindRank();
    Card::Rank otherThreeRank = otherHand.getThreeOfAKindRank();

    int myThreeValue = static_cast<int>(myThreeRank);
    int otherThreeValue = static_cast<int>(otherThreeRank);

    if (myThreeValue > otherThreeValue) {
        return 1;
    }
    if (myThreeValue < otherThreeValue) {
        return -1;
    }

    return 0;
}

Card::Rank Penthouse::getThreeOfAKindRank() const {
    QMap<Card::Rank, int> rankCounts = HandUtils::getRankCounts(m_cards);

    for (auto it = rankCounts.begin(); it != rankCounts.end(); ++it) {
        if (it.value() == 3) {
            return it.key();
        }
    }

    return Card::Rank::Rank2; // default value
}
