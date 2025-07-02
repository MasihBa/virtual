#include "handutils.h"

namespace HandUtils {

void sortHandDescending(QVector<Card>& hand) {
    std::sort(hand.begin(), hand.end());
    std::reverse(hand.begin(), hand.end());
}

QMap<Card::Rank, int> getRankCounts(const QVector<Card>& hand) {
    QMap<Card::Rank, int> counts;
    for (const Card& card : hand) {
        counts[card.getRank()]++;
    }
    return counts;
}

bool isFlush(const QVector<Card>& hand) {
    if (hand.isEmpty()) return false;
    Card::Unit firstUnit = hand.first().getUnit();
    for (const Card& card : hand) {
        if (card.getUnit() != firstUnit) {
            return false;
        }
    }
    return true;
}

bool isStraight(const QVector<Card>& hand) {
    if (hand.size() != 5) return false;
        for (int i = 0; i < 4; ++i) {
            if (hand[i].getRankValue() != hand[i+1].getRankValue() + 1) {
                return false;
            }
        }
    return true;
}

} // namespace HandUtils
