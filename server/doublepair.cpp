// doublepair.cpp

#include "doublepair.h"
#include "handutils.h"
#include <algorithm>

DoublePair::DoublePair(const QVector<Card>& cards) {
    m_cards = cards;

    if (m_cards.size() == 5) {
        m_highPairRankValue = m_cards[0].getRankValue();
        m_lowPairRankValue  = m_cards[2].getRankValue();
        m_kickerRankValue   = m_cards[4].getRankValue();
    }
}

int DoublePair::getStrength() const {
    return 3;
}

QString DoublePair::getName() const {
    return "Hand Pair Double";
}

std::unique_ptr<HandPattern> DoublePair::evaluate(const QVector<Card>& sortedHand) const {
    QMap<Card::Rank, int> rankCounts = HandUtils::getRankCounts(sortedHand);

    if (rankCounts.size() != 3) {
        return nullptr;
    }

    QVector<Card::Rank> pairRanks;
    Card::Rank kickerRank;
    int pairCount = 0;

    for (auto it = rankCounts.constBegin(); it != rankCounts.constEnd(); ++it) {
        if (it.value() == 2) {
            pairCount++;
            pairRanks.push_back(it.key());
        } else if (it.value() == 1) {
            kickerRank = it.key();
        }
    }

    if (pairCount == 2) {

        std::sort(pairRanks.begin(), pairRanks.end(), [](Card::Rank a, Card::Rank b) {
            return static_cast<int>(a) > static_cast<int>(b);
        });

        Card::Rank highPairRank = pairRanks[0];
        Card::Rank lowPairRank = pairRanks[1];
        QVector<Card> reorderedHand;
        QVector<Card> highPairCards, lowPairCards, kickerCards;

        for (const Card& card : sortedHand) {
            if (card.getRank() == highPairRank) {
                highPairCards.push_back(card);
            } else if (card.getRank() == lowPairRank) {
                lowPairCards.push_back(card);
            } else {
                kickerCards.push_back(card);
            }
        }

        reorderedHand.append(highPairCards);
        reorderedHand.append(lowPairCards);
        reorderedHand.append(kickerCards);

        return std::make_unique<DoublePair>(reorderedHand);
    }
    return nullptr;
}

int DoublePair::compare(const HandPattern& other) const {
    const auto& otherHand = dynamic_cast<const DoublePair&>(other);
    if (m_highPairRankValue > otherHand.m_highPairRankValue) return 1;
    if (m_highPairRankValue < otherHand.m_highPairRankValue) return -1;
    if (m_lowPairRankValue > otherHand.m_lowPairRankValue) return 1;
    if (m_lowPairRankValue < otherHand.m_lowPairRankValue) return -1;
    if (m_kickerRankValue > otherHand.m_kickerRankValue) return 1;
    if (m_kickerRankValue < otherHand.m_kickerRankValue) return -1;
    return 0;
}
