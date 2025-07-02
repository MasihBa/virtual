#ifndef GAMER_H
#define GAMER_H

#include <QObject>
#include <QString>
#include "card.h"
#include "handpattern.h"
#include <memory>
class Gamer : public QObject
{
    Q_OBJECT
public:
    explicit Gamer(qintptr id ,QString _username,QObject *parent = nullptr);
    qintptr getID() const {return ID;}
    QString getUserName() const {return username;}
    void setStatusRound(int round,int result) {statusInRound[round] = result;}
    int gettStatusRound(int round) {return statusInRound[round];}
    int numOfWins();
    void addCard(const Card& _card);
    QVector<Card> getHand() const { return hand; }
    void setHandPattern(std::unique_ptr<HandPattern> pattern);
    const HandPattern* getHandPattern() const;
    void clearHand();
    bool hasCompleteHand() const { return hand.size() == 5; }
    void addRoundWin(int roundIdx);
    int getRoundWins() const;
private:
    qintptr ID;
    QString username;
    QVector<Card> hand;
    int statusInRound[3];
    std::unique_ptr<HandPattern> m_handPattern;
signals:
};

#endif // GAMER_H
