// mschand.cpp

#include "mschand.h"
#include "handutils.h"

MscHand::MscHand(const QVector<Card>& cards) {
    m_cards = cards;
}

int MscHand::getStrength() const {
    return 6;
}

QString MscHand::getName() const {
    return "Hand MSC";
}

std::unique_ptr<HandPattern> MscHand::evaluate(const QVector<Card>& sortedHand) const {

    if (HandUtils::isFlush(sortedHand)) {
        return std::make_unique<MscHand>(sortedHand);
    }
    return nullptr;
}

int MscHand::compare(const HandPattern& other) const {
    const auto& otherHand = dynamic_cast<const MscHand&>(other);

    for (int i = 0; i < m_cards.size(); ++i) {
        if (m_cards[i].getRankValue() > otherHand.m_cards[i].getRankValue()) {
            return 1;
        }
        if (m_cards[i].getRankValue() < otherHand.m_cards[i].getRankValue()) {
            return -1;
        }
    }
    return 0;
}
