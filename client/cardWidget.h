#ifndef CARDWIDGET_H
#define CARDWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QEnterEvent>
#include <QPainter>
#include <QDebug>

class CardWidget : public QWidget {
    Q_OBJECT

public:
    enum Suit {
        DIAMOND = 4,
        GOLD = 3,
        DOLLAR = 2,
        COIN = 1
    };

    enum Rank {
        TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
        SOLDIER = 11,
        QUEEN = 12,
        KING = 13,
        BITCOIN = 14
    };

    explicit CardWidget(QWidget* parent = nullptr);
    explicit CardWidget(const QString& cardString, QWidget* parent = nullptr);
    explicit CardWidget(Suit suit, Rank rank, QWidget* parent = nullptr);
    ~CardWidget();
    void setCard(const QString& cardString);
    void setCard(Suit suit, Rank rank);
    void setSelected(bool selected);
    void setClickable(bool clickable);
    void setFaceUp(bool faceUp);
    void setHighlighted(bool highlighted);
    QString getCardString() const;
    Suit getSuit() const;
    Rank getRank() const;
    bool isSelected() const;
    bool isClickable() const;
    bool isFaceUp() const;

signals:
    void cardClicked(CardWidget* card);
    void cardDoubleClicked(CardWidget* card);
    void cardHovered(CardWidget* card, bool entered);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;

private:
    Suit m_suit;
    Rank m_rank;

    bool m_isSelected;
    bool m_isClickable;
    bool m_isFaceUp;
    bool m_isHovered;
    bool m_isHighlighted;

    QPixmap m_frontImage;
    QPixmap m_backImage;

    QPropertyAnimation* m_selectionAnimation;
    QPropertyAnimation* m_hoverAnimation;

    void initializeWidget();
    void parseCardString(const QString& cardString);
    void loadCardImages();
    void updateCardImage();
    void animateSelection();
    void animateHover(bool entered);

    QString suitToString(Suit suit) const;
    QString rankToString(Rank rank) const;
    Suit stringToSuit(const QString& suitStr) const;
    Rank stringToRank(const QString& rankStr) const;
};

#endif // CARDWIDGET_H
