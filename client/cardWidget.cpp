#include "cardWidget.h"
#include <QApplication>
#include <QGraphicsEffect>
#include <QGraphicsDropShadowEffect>


// this is the cardWidget defualt constructor
CardWidget::CardWidget(QWidget* parent)
    : QWidget(parent)
    , m_suit(COIN)
    , m_rank(TWO)
    , m_isSelected(false)
    , m_isClickable(true)
    , m_isFaceUp(true)
    , m_isHovered(false)
    , m_isHighlighted(false)
    , m_selectionAnimation(nullptr)
    , m_hoverAnimation(nullptr)
{
    initializeWidget();
}

// this is the cardWidget constructor with a QString of cardString
CardWidget::CardWidget(const QString& cardString, QWidget* parent)
    : QWidget(parent)
    , m_isSelected(false)
    , m_isClickable(true)
    , m_isFaceUp(true)
    , m_isHovered(false)
    , m_isHighlighted(false)
    , m_selectionAnimation(nullptr)
    , m_hoverAnimation(nullptr)
{
    initializeWidget();
    setCard(cardString);
}

// this is the cosntructor with enum suit and enum rank
CardWidget::CardWidget(Suit suit, Rank rank, QWidget* parent)
    : QWidget(parent), m_suit(suit), m_rank(rank)
{
    QString frontImagePath = QString(":/cards/front/%1_%2.png")
                                 .arg(suitToString(m_suit).toLower())
                                 .arg(rankToString(m_rank).toLower());

    m_frontImage.load(frontImagePath);

    m_backImage.load(":/cards/back/card_back.png");

    m_isFaceUp = true;
    m_isSelected = false;
    m_isClickable = true;
    m_isHovered = false;
    m_isHighlighted = false;

    setFixedSize(80, 120);
    if (m_frontImage.isNull()) {
        qDebug() << "Error: the image of the card was not loaded: " << frontImagePath;
    }
}


CardWidget::~CardWidget() {
    if (m_selectionAnimation) {
        m_selectionAnimation->deleteLater();
    }
    if (m_hoverAnimation) {
        m_hoverAnimation->deleteLater();
    }
}

void CardWidget::setCard(const QString& cardString) {
    parseCardString(cardString);
    updateCardImage();
    update();
}

void CardWidget::setCard(Suit suit, Rank rank) {
    m_suit = suit;
    m_rank = rank;
    updateCardImage();
    update();
}

void CardWidget::setSelected(bool selected) {
    if (m_isSelected != selected) {
        m_isSelected = selected;
        animateSelection();
        update();
    }
}

void CardWidget::setClickable(bool clickable) {
    m_isClickable = clickable;
    setCursor(clickable ? Qt::PointingHandCursor : Qt::ArrowCursor);
}

void CardWidget::setFaceUp(bool faceUp) {
    m_isFaceUp = faceUp;
    update();
}

QString CardWidget::getCardString() const {
    return suitToString(m_suit) + "_" + rankToString(m_rank);
}

CardWidget::Suit CardWidget::getSuit() const {
    return m_suit;
}

CardWidget::Rank CardWidget::getRank() const {
    return m_rank;
}

bool CardWidget::isSelected() const {
    return m_isSelected;
}

bool CardWidget::isClickable() const {
    return m_isClickable;
}

bool CardWidget::isFaceUp() const {
    return m_isFaceUp;
}

void CardWidget::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton && m_isClickable) {
        emit cardClicked(this);
    }
    QWidget::mousePressEvent(event);
}

void CardWidget::mouseDoubleClickEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton && m_isClickable) {
        emit cardDoubleClicked(this);
    }
    QWidget::mouseDoubleClickEvent(event);
}

void CardWidget::enterEvent(QEnterEvent* event) {// when keep the mouse on a card
    m_isHovered = true;
    emit cardHovered(this, true);
    animateHover(true);
    update();
    QWidget::enterEvent(event);
}

void CardWidget::leaveEvent(QEvent* event) {// when don't keep the mouse on a card
    m_isHovered = false;
    emit cardHovered(this, false);
    animateHover(false);
    update();
    QWidget::leaveEvent(event);
}

void CardWidget::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QRect cardRect = rect().adjusted(2, 2, -2, -2);
    if (m_isSelected) {
        painter.setPen(QPen(QColor(0, 120, 215), 3));
        painter.setBrush(QColor(0, 120, 215, 30));
    } else if (m_isHighlighted) {
        painter.setPen(QPen(QColor(255, 165, 0), 2));
        painter.setBrush(QColor(255, 165, 0, 20));
    } else if (m_isHovered) {
        painter.setPen(QPen(QColor(128, 128, 128), 1));
        painter.setBrush(QColor(128, 128, 128, 10));
    } else {
        painter.setPen(QPen(QColor(200, 200, 200), 1));
        painter.setBrush(Qt::white);
    }
    painter.drawRoundedRect(cardRect, 8, 8);
    QPixmap currentImage = m_isFaceUp ? m_frontImage : m_backImage;
    if (!currentImage.isNull()) {
        QRect imageRect = cardRect.adjusted(4, 4, -4, -4);
        painter.drawPixmap(imageRect, currentImage);
    } else {
        painter.setPen(Qt::black);
        painter.drawText(cardRect, Qt::AlignCenter, getCardString());
    }

    if (!m_isClickable) {
        painter.fillRect(cardRect, QColor(128, 128, 128, 100));
    }
}

// For change ENUM to string(suit)
QString CardWidget::suitToString(Suit suit) const {
    switch (suit) {
    case DIAMOND: return "diamond";
    case DOLLAR:  return "dollar";
    case COIN:    return "coin";
    case GOLD:    return "gold";
    default:      return "unknown";
    }
}

// For change ENUM to string(rank)
QString CardWidget::rankToString(Rank rank) const {
    switch (rank) {
    case TWO:     return "2";
    case THREE:   return "3";
    case FOUR:    return "4";
    case FIVE:    return "5";
    case SIX:     return "6";
    case SEVEN:   return "7";
    case EIGHT:   return "8";
    case NINE:    return "9";
    case TEN:     return "10";
    case SOLDIER: return "soldier";
    case QUEEN:   return "queen";
    case KING:    return "king";
    case BITCOIN: return "bitcoin";
    default:      return "unknown";
    }
}

void CardWidget::initializeWidget() {
    setFixedSize(80, 120);
    setCursor(Qt::PointingHandCursor);
    setAttribute(Qt::WA_StyledBackground, true);

    m_selectionAnimation = new QPropertyAnimation(this, "geometry");
    m_selectionAnimation->setDuration(200);

    m_hoverAnimation = new QPropertyAnimation(this, "geometry");
    m_hoverAnimation->setDuration(150);
}

void CardWidget::parseCardString(const QString& cardString) {
    QStringList parts = cardString.split("_");
    if (parts.size() == 2) {
        m_suit = stringToSuit(parts[0]);
        m_rank = stringToRank(parts[1]);
    }
}

void CardWidget::updateCardImage() {
    QString imagePath = QString(":/cards/%1_%2.png"). arg(suitToString(m_suit)). arg(rankToString(m_rank));
    m_frontImage = QPixmap(imagePath);
    m_backImage = QPixmap(":/cards/card_back.png");
}

void CardWidget::animateSelection() {
    if (!m_selectionAnimation) return;

    QRect currentGeometry = geometry();
    QRect targetGeometry = m_isSelected? currentGeometry.adjusted(-2, -4, 2, 0): currentGeometry.adjusted(2, 4, -2, 0);
    m_selectionAnimation->setStartValue(currentGeometry);
    m_selectionAnimation->setEndValue(targetGeometry);
    m_selectionAnimation->start();
}

void CardWidget::animateHover(bool entered) {
    if (!m_hoverAnimation) return;

    QRect currentGeometry = geometry();
    QRect targetGeometry = entered ?currentGeometry.adjusted(-1, -2, 1, 0) :currentGeometry.adjusted(1, 2, -1, 0);

    m_hoverAnimation->setStartValue(currentGeometry);
    m_hoverAnimation->setEndValue(targetGeometry);
    m_hoverAnimation->start();
}

CardWidget::Suit CardWidget::stringToSuit(const QString& suitStr) const {
    QString lower = suitStr.toLower();
    if (lower == "diamond") return DIAMOND;
    if (lower == "gold")    return GOLD;
    if (lower == "dollar")  return DOLLAR;
    if (lower == "coin")    return COIN;
    return COIN; // default value............................
}

CardWidget::Rank CardWidget::stringToRank(const QString& rankStr) const {
    QString lower = rankStr.toLower();
    if (lower == "2")       return TWO;
    if (lower == "3")       return THREE;
    if (lower == "4")       return FOUR;
    if (lower == "5")       return FIVE;
    if (lower == "6")       return SIX;
    if (lower == "7")       return SEVEN;
    if (lower == "8")       return EIGHT;
    if (lower == "9")       return NINE;
    if (lower == "10")      return TEN;
    if (lower == "soldier") return SOLDIER;
    if (lower == "queen")   return QUEEN;
    if (lower == "king")    return KING;
    if (lower == "bitcoin") return BITCOIN;
    return TWO; // default value............................
}

void CardWidget::setHighlighted(bool highlighted) {
    if (m_isHighlighted != highlighted) {
        m_isHighlighted = highlighted;
        update();
    }
}

void CardWidget::loadCardImages() {
    QString frontImagePath = QString(":/cards/front/%1_%2.png")
    .arg(suitToString(m_suit).toLower())
        .arg(rankToString(m_rank).toLower());

    m_frontImage.load(frontImagePath);
    m_backImage.load(":/cards/back/card_back.png");

    if (m_frontImage.isNull()) {
        qDebug() << "Error: could not load card image:" << frontImagePath;
    }
}
