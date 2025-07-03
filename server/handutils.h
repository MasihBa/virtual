#ifndef HANDUTILS_H
#define HANDUTILS_H

#include "card.h"
#include <QVector>
#include <QMap>
#include <algorithm>

namespace HandUtils {
void sortHandDescending(QVector<Card>& hand);
QMap<Card::Rank, int> getRankCounts(const QVector<Card>& hand);
bool isFlush(const QVector<Card>& hand);
bool isStraight(const QVector<Card>& hand);
}

#endif // HANDUTILS_H
