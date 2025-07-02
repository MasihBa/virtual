// singlepair.cpp
#include "singlepair.h"
#include "handutils.h"
#include <algorithm>
#include <memory>

SinglePair::SinglePair(const QVector<Card>& cards) {
    m_cards = cards;

    if (m_cards.size() == 5) {
        m_pairRankValue = m_cards[0].getRankValue();
        m_kicker1Value  = m_cards[2].getRankValue();
        m_kicker2Value  = m_cards[3].getRankValue();
        m_kicker3Value  = m_cards[4].getRankValue();
    }
}

int SinglePair::getStrength() const {
    return 2;
}

QString SinglePair::getName() const {
    return "Hand Pair Single";
}

std::unique_ptr<HandPattern> SinglePair::evaluate(const QVector<Card>& sortedHand) const {
    QMap<Card::Rank, int> rankCounts = HandUtils::getRankCounts(sortedHand);

    if (rankCounts.size() != 4) {
        return nullptr;
    }

    Card::Rank pairRank;
    QVector<Card> pairCards;
    QVector<Card> kickerCards;

    for (auto it = rankCounts.constBegin(); it != rankCounts.constEnd(); ++it) {
        if (it.value() == 2) {
            pairRank = it.key();
            break;
        }
    }

    for (const Card& card : sortedHand) {
        if (card.getRank() == pairRank) {
            pairCards.push_back(card);
        } else {
            kickerCards.push_back(card);
        }
    }
    QVector<Card> reorderedHand;
    reorderedHand.append(pairCards);
    reorderedHand.append(kickerCards);
    return std::make_unique<SinglePair>(reorderedHand);
}

int SinglePair::compare(const HandPattern& other) const {
    const auto& otherHand = dynamic_cast<const SinglePair&>(other);
    if (m_pairRankValue > otherHand.m_pairRankValue) return 1;
    if (m_pairRankValue < otherHand.m_pairRankValue) return -1;

    if (m_kicker1Value > otherHand.m_kicker1Value) return 1;
    if (m_kicker1Value < otherHand.m_kicker1Value) return -1;

    if (m_kicker2Value > otherHand.m_kicker2Value) return 1;
    if (m_kicker2Value < otherHand.m_kicker2Value) return -1;

    if (m_kicker3Value > otherHand.m_kicker3Value) return 1;
    if (m_kicker3Value < otherHand.m_kicker3Value) return -1;

    return 0;
}
