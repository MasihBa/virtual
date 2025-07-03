#include "gameui.h"
#include "ui_gameui.h"
#include <QDebug>

GameUI::GameUI(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameUI)
    , m_gameControlsEnabled(true)
{
    ui->setupUi(this);
    setupUI();
    connectSignals();
    resetGameUI();
}

GameUI::~GameUI()
{
    delete ui;
}

void GameUI::setupUI()
{
    ui->timerlabel->setAlignment(Qt::AlignCenter);
    ui->timerlabel->setStyleSheet(
        "QLabel { "
        "background-color: black; "
        "color: white; "
        "font-size: 16px; "
        "font-weight: bold; "
        "border: 2px solid white; "
        "border-radius: 5px; "
        "padding: 5px; "
        "}"
        );

    ui->stopButton->setText("Stop");
    ui->resumeButton->setText("Resume");
    ui->resumeButton->setEnabled(false);
    ui->exitButton->setText("Exit");

    QString cardButtonStyle =
        "QPushButton { "
        "border: 2px solid #333; "
        "border-radius: 8px; "
        "background-color: #f0f0f0; "
        "}"
        "QPushButton:hover { "
        "border: 2px solid #0078d4; "
        "}"
        "QPushButton:pressed { "
        "background-color: #e0e0e0; "
        "}"
        "QPushButton:disabled { "
        "background-color: #cccccc; "
        "border: 2px solid #999; "
        "}";

    for(int i = 1; i <= 7; i++) {
        QPushButton* btn = getRequestedCardButton(i-1);
        if(btn) {
            btn->setStyleSheet(cardButtonStyle);
            btn->setText("");
        }
    }

    for(int i = 1; i <= 5; i++) {
        QPushButton* btn = getSelectedCardButton(i-1);
        if(btn) {
            btn->setStyleSheet(cardButtonStyle);
            btn->setText("");
            btn->setEnabled(false);
        }
    }

    setupChatUI();// the new function for chat
}
// the new function for chat
void GameUI::setupChatUI()
{

    this->setContentsMargins(0, 0, 0, 0);

    this->setStyleSheet(
        "GameUI { "
        "background-image: url(:/gamepage/table/Game-Ground-Photo.JPG); "
        "background-repeat: no-repeat; "
        "background-position: center; "
        "background-size: cover; "
        "margin: 0px; "
        "padding: 0px; "
        "}"
        );
    m_chatDisplay = new QTextEdit(this);
    m_chatInput = new QLineEdit(this);
    m_sendButton = new QPushButton("Send", this);
    m_stickerPanel = new QFrame(this);

    m_chatDisplay->setReadOnly(true);
    m_chatDisplay->setMaximumHeight(200);
    m_chatDisplay->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_chatDisplay->setStyleSheet(
        "QTextEdit {"
        "background-color: #f5f5f5;"
        "border: 2px solid #ddd;"
        "border-radius: 8px;"
        "padding: 5px;"
        "font-size: 12px;"
        "}"
        );

    m_chatInput->setPlaceholderText("Type your message...");
    m_chatInput->setMaxLength(200);
    m_chatInput->setStyleSheet(
        "QLineEdit {"
        "border: 2px solid #ddd;"
        "border-radius: 5px;"
        "padding: 5px;"
        "font-size: 12px;"
        "}"
        );

    m_sendButton->setStyleSheet(
        "QPushButton {"
        "background-color: #0078d4;"
        "color: white;"
        "border: none;"
        "border-radius: 5px;"
        "padding: 8px 15px;"
        "font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "background-color: #106ebe;"
        "}"
        "QPushButton:pressed {"
        "background-color: #005a9e;"
        "}"
        );

    setupStickerPanel();

    QVBoxLayout* chatLayout = new QVBoxLayout();
    QHBoxLayout* inputLayout = new QHBoxLayout();

    chatLayout->addWidget(new QLabel("Game Chat:"));
    chatLayout->addWidget(m_chatDisplay);
    chatLayout->addWidget(m_stickerPanel);

    inputLayout->addWidget(m_chatInput);
    inputLayout->addWidget(m_sendButton);
    chatLayout->addLayout(inputLayout);

    ui->chatFrame->setLayout(chatLayout);

    connect(m_sendButton, &QPushButton::clicked, this, &GameUI::sendChatMessage);
    connect(m_chatInput, &QLineEdit::returnPressed, this, &GameUI::sendChatMessage);
}

// the new function for chat
void GameUI::setupStickerPanel()
{
    m_availableStickers = {"😄", "😢", "😡", "😎", "👍", "❤️"};
    QHBoxLayout* stickerLayout = new QHBoxLayout(m_stickerPanel);
    stickerLayout->setSpacing(5);
    for(int i = 0; i < m_availableStickers.size(); i++) {
        QPushButton* stickerBtn = new QPushButton(m_availableStickers[i], m_stickerPanel);
        stickerBtn->setFixedSize(30, 30);
        stickerBtn->setStyleSheet(
            "QPushButton {"
            "border: 1px solid #ddd;"
            "border-radius: 15px;"
            "background-color: white;"
            "font-size: 16px;"
            "}"
            "QPushButton:hover {"
            "background-color: #e6f3ff;"
            "border: 2px solid #0078d4;"
            "}"
            );
        connect(stickerBtn, &QPushButton::clicked, [this, i]() {
            addStickerToMessage(m_availableStickers[i]);
        });
        stickerLayout->addWidget(stickerBtn);
    }
    stickerLayout->addStretch();
}

// void GameUI::sendChatMessage()
// {
//     QString message = m_chatInput->text().trimmed();
//     if(message.isEmpty()) return;

//     m_chatInput->clear();
//     emit chatMessageSent(message);
// }

void GameUI::sendChatMessage()
{
    if (!m_chatInput) return;
    QString message = m_chatInput->text().trimmed();
    if(message.isEmpty()) return;
    m_chatInput->clear();
    emit chatMessageSent(message);
}

// void GameUI::displayChatMessage(const QString& username, const QString& message)
// {
//     QString timestamp = QTime::currentTime().toString("hh:mm");
//     QString formattedMessage = QString("<span style='color: #666;'>[%1]</span> "
//                                        "<span style='color: #0078d4; font-weight: bold;'>%2:</span> "
//                                        "<span style='color: #333;'>%3</span>")
//                                    .arg(timestamp)
//                                    .arg(username)
//                                    .arg(message);

//     m_chatDisplay->append(formattedMessage);

//     QScrollBar* scrollBar = m_chatDisplay->verticalScrollBar();
//     scrollBar->setValue(scrollBar->maximum());
// }

void GameUI::displayChatMessage(const QString& username, const QString& message)
{
    if (!m_chatDisplay) {
        qWarning() << "Chat display not initialized!";
        return;
    }

    QString timestamp = QTime::currentTime().toString("hh:mm");
    QString formattedMessage = QString("<div style='margin: 2px 0;'>"
                                     "<span style='color: #666; font-size: 10px;'>[%1]</span> "
                                     "<span style='color: #0078d4; font-weight: bold;'>%2:</span> "
                                     "<span style='color: #333;'>%3</span>"
                                     "</div>")
                                .arg(timestamp)
                                .arg(username)
                                .arg(message);

    m_chatDisplay->append(formattedMessage);

    QScrollBar* scrollBar = m_chatDisplay->verticalScrollBar();
    scrollBar->setValue(scrollBar->maximum());
    if (m_chatDisplay->document()->lineCount() > 100) {
        QString allText = m_chatDisplay->toHtml();
        QStringList lines = allText.split("");
        if (lines.size() > 10) {
            lines.removeFirst();
            lines.removeFirst();
            m_chatDisplay->setHtml(lines.join(""));
        }
    }
}

// void GameUI::addStickerToMessage(const QString& sticker)
// {
//     QString currentText = m_chatInput->text();
//     m_chatInput->setText(currentText + sticker);
//     m_chatInput->setFocus();
// }

void GameUI::addStickerToMessage(const QString& sticker)
{
    if (m_chatInput) {
        QString currentText = m_chatInput->text();
        m_chatInput->setText(currentText + sticker);
        m_chatInput->setFocus();
    }
}

void GameUI::connectSignals()
{
    connect(ui->requestedCardButton1, &QPushButton::clicked, this, &GameUI::onRequestedCard1Clicked);
    connect(ui->requestedCardButton2, &QPushButton::clicked, this, &GameUI::onRequestedCard2Clicked);
    connect(ui->requestedCardButton3, &QPushButton::clicked, this, &GameUI::onRequestedCard3Clicked);
    connect(ui->requestedCardButton5_2, &QPushButton::clicked, this, &GameUI::onRequestedCard5Clicked);
    connect(ui->requestedCardButton6, &QPushButton::clicked, this, &GameUI::onRequestedCard6Clicked);
    connect(ui->requestedCardButton4_2, &QPushButton::clicked, this, &GameUI::onRequestedCard4Clicked);
    connect(ui->requestedCardButton7, &QPushButton::clicked, this, &GameUI::onRequestedCard7Clicked);
    connect(ui->selectedCardButton1, &QPushButton::clicked, this, &GameUI::onSelectedCard1Clicked);
    connect(ui->selectedCardButton2, &QPushButton::clicked, this, &GameUI::onSelectedCard2Clicked);
    connect(ui->selectedCardButton3, &QPushButton::clicked, this, &GameUI::onSelectedCard3Clicked);
    connect(ui->selectedCardButton4, &QPushButton::clicked, this, &GameUI::onSelectedCard4Clicked);
    connect(ui->selectedCardButton5, &QPushButton::clicked, this, &GameUI::onSelectedCard5Clicked);

    connect(ui->stopButton, &QPushButton::clicked, this, &GameUI::onStopClicked);
    connect(ui->resumeButton, &QPushButton::clicked, this, &GameUI::onResumeClicked);
    connect(ui->exitButton, &QPushButton::clicked, this, &GameUI::onExitClicked);
}

void GameUI::updateRequestedCards(const QStringList& cardNames)
{
    m_currentRequestedCards = cardNames;
    clearRequestedCards();

    for(int i = 0; i < qMin(cardNames.size(), 7); i++) {
        setRequestedCardImage(i, cardNames[i]);
    }

    qDebug() << "Updated requested cards:" << cardNames;
}

void GameUI::updateSelectedCards(const QStringList& cardNames)
{
    m_currentSelectedCards = cardNames;
    clearSelectedCards();

    for(int i = 0; i < qMin(cardNames.size(), 5); i++) {
        setSelectedCardImage(i, cardNames[i]);
    }

    qDebug() << "Updated selected cards:" << cardNames;
}

void GameUI::setTimerDisplay(int seconds)
{
    ui->timerlabel->setText(QString::number(seconds));
}

void GameUI::enableGameControls(bool enabled)
{
    m_gameControlsEnabled = enabled;

    for(int i = 0; i < 7; i++) {
        QPushButton* btn = getRequestedCardButton(i);
        if(btn && btn->isVisible()) {
            btn->setEnabled(enabled);
        }
    }

    ui->stopButton->setEnabled(enabled);
    ui->exitButton->setEnabled(enabled);
}

void GameUI::resetGameUI()
{
    clearRequestedCards();
    clearSelectedCards();
    m_currentRequestedCards.clear();
    m_currentSelectedCards.clear();
    setTimerDisplay(0);
    enableGameControls(true);
    ui->resumeButton->setEnabled(false);
    ui->stopButton->setText("Stop");
}

// void GameUI::markCardAsSelected(int index)
// {
//     if (index >= 0 && index < m_currentSelectedCards.size()) {
//         m_currentSelectedCards[index] = "selected_card";
//         setSelectedCardImage(index, "selected_card");
//         qDebug() << "Marked card at index" << index << "as selected";
//     }
// }

// this function was changed to show the selected card in gameUI
void GameUI::markCardAsSelected(int index)
{
    if (index >= 0 && m_currentSelectedCards.size() < 5) {
        QString selectedCard = "selected_card";
        m_currentSelectedCards.append(selectedCard);
        int selectedIndex = m_currentSelectedCards.size() - 1;
        setSelectedCardImage(selectedIndex, selectedCard);

        qDebug() << "Added selected card at index:" << selectedIndex;
        qDebug() << "Current selected cards:" << m_currentSelectedCards;
    }
}


void GameUI::updateStopButtonAppearance(const QString& text, bool enabled)
{
    if (ui && ui->stopButton) {
        ui->stopButton->setText(text);
        ui->stopButton->setEnabled(enabled);
    }
}

void GameUI::setRequestedCardImage(int index, const QString& cardName)
{
    QPushButton* btn = getRequestedCardButton(index);
    if(!btn || !isValidCardName(cardName)) return;

    QPixmap cardPixmap = loadCardImage(cardName);
    if(!cardPixmap.isNull()) {
        QSize buttonSize = btn->size();
        QPixmap scaledPixmap = cardPixmap.scaled(buttonSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

        btn->setIcon(QIcon(scaledPixmap));
        btn->setIconSize(buttonSize);
        btn->setEnabled(m_gameControlsEnabled);
        btn->setVisible(true);

        qDebug() << "Set requested card image:" << cardName << "at index:" << index;
    } else {
        qWarning() << "Failed to load card image:" << cardName;
        btn->setText(cardName);
        btn->setEnabled(m_gameControlsEnabled);
        btn->setVisible(true);
    }
}

void GameUI::setSelectedCardImage(int index, const QString& cardName)
{
    QPushButton* btn = getSelectedCardButton(index);
    if(!btn || !isValidCardName(cardName)) return;

    QPixmap cardPixmap = loadCardImage(cardName);
    if(!cardPixmap.isNull()) {
        QSize buttonSize = btn->size();
        QPixmap scaledPixmap = cardPixmap.scaled(buttonSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

        btn->setIcon(QIcon(scaledPixmap));
        btn->setIconSize(buttonSize);
        btn->setEnabled(false);
        btn->setVisible(true);

        qDebug() << "Set selected card image:" << cardName << "at index:" << index;
    } else {
        qWarning() << "Failed to load card image:" << cardName;
        btn->setText(cardName);
        btn->setEnabled(false);
        btn->setVisible(true);
    }
}

QString GameUI::getCardImagePath(const QString& cardName)
{
    if (cardName == "selected_card") {
        return ":/card/cards/selected_card.JPG"; // Special image for selected cards
    }

    if(!isValidCardName(cardName)) return QString();
    return QString(":/card/cards/%1.JPG").arg(cardName);
}

bool GameUI::isValidCardName(const QString& cardName)
{
    if (cardName == "selected_card") return true;
    if(cardName.isEmpty()) return false;
    QStringList parts = cardName.split('-');
    if(parts.size() != 2) return false;
    QString unit = parts[0];
    QString rank = parts[1];
    QStringList validUnits = {"Gold", "Diamond", "Dollar", "Coin"};
    if(!validUnits.contains(unit)) return false;
    QStringList validRanks = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Soldier", "Queen", "King", "Bitcoin"};
    if(!validRanks.contains(rank)) return false;
    return true;
}

QPixmap GameUI::loadCardImage(const QString& cardName)
{
    QString imagePath = getCardImagePath(cardName);
    QPixmap pixmap(imagePath);
    if(pixmap.isNull()) {
        qWarning() << "Could not load image from path:" << imagePath;
    }
    return pixmap;
}

QPushButton* GameUI::getRequestedCardButton(int index)
{
    switch(index) {
    case 0: return ui->requestedCardButton1;
    case 1: return ui->requestedCardButton2;
    case 2: return ui->requestedCardButton3;
    case 3: return ui->requestedCardButton4_2;
    case 4: return ui->requestedCardButton5_2;
    case 5: return ui->requestedCardButton6;
    case 6: return ui->requestedCardButton7;
    default: return nullptr;
    }
}

QPushButton* GameUI::getSelectedCardButton(int index)
{
    switch(index) {
    case 0: return ui->selectedCardButton1;
    case 1: return ui->selectedCardButton2;
    case 2: return ui->selectedCardButton3;
    case 3: return ui->selectedCardButton4;
    case 4: return ui->selectedCardButton5;
    default: return nullptr;
    }
}

void GameUI::clearRequestedCards()
{
    for(int i = 0; i < 7; i++) {
        QPushButton* btn = getRequestedCardButton(i);
        if(btn) {
            btn->setIcon(QIcon());
            btn->setText("");
            btn->setVisible(false);
        }
    }
}

void GameUI::clearSelectedCards()
{
    for(int i = 0; i < 5; i++) {
        QPushButton* btn = getSelectedCardButton(i);
        if(btn) {
            btn->setIcon(QIcon());
            btn->setText("");
            btn->setVisible(false);
        }
    }
}

void GameUI::onRequestedCard1Clicked()
{
    if(m_currentRequestedCards.size() > 0) {
        emit cardSelected(0, m_currentRequestedCards[0]);
    }
}

void GameUI::onRequestedCard2Clicked()
{
    if(m_currentRequestedCards.size() > 1) {
        emit cardSelected(1, m_currentRequestedCards[1]);
    }
}

void GameUI::onRequestedCard3Clicked()
{
    if(m_currentRequestedCards.size() > 2) {
        emit cardSelected(2, m_currentRequestedCards[2]);
    }
}

void GameUI::onRequestedCard4Clicked()
{
    if(m_currentRequestedCards.size() > 3) {
        emit cardSelected(3, m_currentRequestedCards[3]);
    }
}

void GameUI::onRequestedCard5Clicked()
{
    if(m_currentRequestedCards.size() > 4) {
        emit cardSelected(4, m_currentRequestedCards[4]);
    }
}

void GameUI::onRequestedCard6Clicked()
{
    if(m_currentRequestedCards.size() > 5) {
        emit cardSelected(5, m_currentRequestedCards[5]);
    }
}

void GameUI::onRequestedCard7Clicked()
{
    if(m_currentRequestedCards.size() > 6) {
        emit cardSelected(6, m_currentRequestedCards[6]);
    }
}

void GameUI::onSelectedCard1Clicked()
{
    emit selectedCardClicked(0);
    qDebug() << "Selected card 1 clicked (display only)";
}

void GameUI::onSelectedCard2Clicked()
{
    emit selectedCardClicked(1);
    qDebug() << "Selected card 2 clicked (display only)";
}

void GameUI::onSelectedCard3Clicked()
{
    emit selectedCardClicked(2);
    qDebug() << "Selected card 3 clicked (display only)";
}

void GameUI::onSelectedCard4Clicked()
{
    emit selectedCardClicked(3);
    qDebug() << "Selected card 4 clicked (display only)";
}

void GameUI::onSelectedCard5Clicked()
{
    emit selectedCardClicked(4);
    qDebug() << "Selected card 5 clicked (display only)";
}

void GameUI::onStopClicked()
{
    emit stopRequested();
}

void GameUI::onResumeClicked()
{
    emit resumeRequested();
}

void GameUI::onExitClicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Exit", "Do you want to exit?",
        QMessageBox::Yes | QMessageBox::No
        );

    if(reply == QMessageBox::Yes) {
        emit exitRequested();
    }
}

void GameUI::updateGameStatus(const QString& status)
{
    ui->statusLabel->setText(status);

    //statusBar()->showMessage(status);

    qDebug() << "Game Status:" << status;
}
