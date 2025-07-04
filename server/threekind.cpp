// threeofakind.cpp

#include "threekind.h"
#include "handutils.h"

ThreeOfAKind::ThreeOfAKind(const QVector<Card>& cards) {
    m_cards = cards;
    if (m_cards.size() == 5) {
        m_threeRankValue = m_cards[0].getRankValue();
    }
}

int ThreeOfAKind::getStrength() const {
    return 4;
}

QString ThreeOfAKind::getName() const {
    return "Hand 3+2";
}

std::unique_ptr<HandPattern> ThreeOfAKind::evaluate(const QVector<Card>& sortedHand) const {
    QMap<Card::Rank, int> rankCounts = HandUtils::getRankCounts(sortedHand);
    bool hasThree = false;
    Card::Rank rankOfThree;

    for(auto it = rankCounts.constBegin(); it != rankCounts.constEnd(); ++it) {
        if (it.value() == 3) {
            hasThree = true;
            rankOfThree = it.key();
            break;
        }
    }

    if (hasThree && rankCounts.size() == 3) {
        QVector<Card> reorderedHand;
        QVector<Card> kickers;
        for (const Card& card : sortedHand) {
            if (card.getRank() == rankOfThree) {
                reorderedHand.push_back(card);
            } else {
                kickers.push_back(card);
            }
        }
        reorderedHand.append(kickers);

        return std::make_unique<ThreeOfAKind>(reorderedHand);
    }

    return nullptr;
}

int ThreeOfAKind::compare(const HandPattern& other) const {
    const auto& otherHand = dynamic_cast<const ThreeOfAKind&>(other);

    if (m_threeRankValue > otherHand.m_threeRankValue) {
        return 1;
    }
    if (m_threeRankValue < otherHand.m_threeRankValue) {
        return -1;
    }
    return 0;
}
