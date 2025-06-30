// #include "gameui.h"
// #include "ui_gameui.h"
// #include <QDebug>
// #include <QJsonDocument>

// GameUI::GameUI(QWidget *parent)
//     : QWidget(parent)
//     , ui(new Ui::GameUI)
//     , m_socketHandler(nullptr)
//     //, m_stopTimer(new QTimer(this))
//     //, m_gameTimer(new QTimer(this))
//     , m_stopUsageCount(0)
//     , m_gameIsStopped(false)
//     , m_stopTimeRemaining(30)
//     , m_remainingTime(0)
//     , m_gameControlsEnabled(true)
// {
//     ui->setupUi(this);
//     setupUI();
//     m_stopTimer = new QTimer(this);
//     //connect(m_gameTimer, &QTimer::timeout, this, &GameUI::onGameTimerTick);
//     connectSignals();
//     resetGameState();
// }

// GameUI::~GameUI()
// {
//     delete ui;
// }

// void GameUI::setupUI()
// {
//     ui->timerlabel->setAlignment(Qt::AlignCenter);
//     ui->timerlabel->setStyleSheet(
//         "QLabel { "
//         "background-color: black; "
//         "color: white; "
//         "font-size: 16px; "
//         "font-weight: bold; "
//         "border: 2px solid white; "
//         "border-radius: 5px; "
//         "padding: 5px; "
//         "}"
//         );

//     ui->stopButton->setText("Stop");
//     ui->resumeButton->setText("Resume");
//     ui->resumeButton->setEnabled(false);
//     ui->exitButton->setText("Exit");

//     QString cardButtonStyle =
//         "QPushButton { "
//         "border: 2px solid #333; "
//         "border-radius: 8px; "
//         "background-color: #f0f0f0; "
//         "}"
//         "QPushButton:hover { "
//         "border: 2px solid #0078d4; "
//         "}"
//         "QPushButton:pressed { "
//         "background-color: #e0e0e0; "
//         "}"
//         "QPushButton:disabled { "
//         "background-color: #cccccc; "
//         "border: 2px solid #999; "
//         "}";

//     for(int i = 1; i <= 7; i++) {
//         QPushButton* btn = getRequestedCardButton(i-1);
//         if(btn) {
//             btn->setStyleSheet(cardButtonStyle);
//             btn->setText("");
//         }
//     }

//     for(int i = 1; i <= 5; i++) {
//         QPushButton* btn = getSelectedCardButton(i-1);
//         if(btn) {
//             btn->setStyleSheet(cardButtonStyle);
//             btn->setText("");
//             btn->setEnabled(false);
//         }
//     }
// }

// void GameUI::connectSignals()
// {
//     connect(ui->requestedCardButton1, &QPushButton::clicked, this, &GameUI::onRequestedCard1Clicked);
//     connect(ui->requestedCardButton2, &QPushButton::clicked, this, &GameUI::onRequestedCard2Clicked);
//     connect(ui->requestedCardButton3, &QPushButton::clicked, this, &GameUI::onRequestedCard3Clicked);
//     connect(ui->requestedCardButton5_2, &QPushButton::clicked, this, &GameUI::onRequestedCard4Clicked);
//     connect(ui->requestedCardButton6, &QPushButton::clicked, this, &GameUI::onRequestedCard5Clicked);
//     connect(ui->requestedCardButton4_2, &QPushButton::clicked, this, &GameUI::onRequestedCard6Clicked);
//     connect(ui->requestedCardButton7, &QPushButton::clicked, this, &GameUI::onRequestedCard7Clicked);

//     connect(ui->selectedCardButton3, &QPushButton::clicked, this, &GameUI::onSelectedCard1Clicked);
//     connect(ui->selectedCardButton1, &QPushButton::clicked, this, &GameUI::onSelectedCard2Clicked);
//     connect(ui->selectedCardButton2, &QPushButton::clicked, this, &GameUI::onSelectedCard3Clicked);
//     connect(ui->selectedCardButton4, &QPushButton::clicked, this, &GameUI::onSelectedCard4Clicked);
//     connect(ui->selectedCardButton5, &QPushButton::clicked, this, &GameUI::onSelectedCard5Clicked);
//     connect(ui->stopButton, &QPushButton::clicked, this, &GameUI::onStopClicked);
//     connect(ui->resumeButton, &QPushButton::clicked, this, &GameUI::onResumeClicked);
//     connect(ui->exitButton, &QPushButton::clicked, this, &GameUI::onExitClicked);
//     connect(m_gameTimer, &QTimer::timeout, this, &GameUI::onTimerTick);
// }

// void GameUI::updateRequestedCards(const QStringList& cardNames)
// {
//     m_currentRequestedCards = cardNames;
//     clearRequestedCards();

//     for(int i = 0; i < qMin(cardNames.size(), 7); i++) {
//         setRequestedCardImage(i, cardNames[i]);
//     }

//     qDebug() << "Updated requested cards:" << cardNames;
// }


// void GameUI::updateSelectedCards(const QStringList& cardNames)
// {
//     m_currentSelectedCards = cardNames;
//     clearSelectedCards();

//     for(int i = 0; i < qMin(cardNames.size(), 5); i++) {
//         setSelectedCardImage(i, cardNames[i]);
//     }

//     qDebug() << "Updated selected cards:" << cardNames;
// }

// void GameUI::setRequestedCardImage(int index, const QString& cardName)
// {
//     QPushButton* btn = getRequestedCardButton(index);
//     if(!btn || !isValidCardName(cardName)) return;

//     QPixmap cardPixmap = loadCardImage(cardName);
//     if(!cardPixmap.isNull()) {
//         QSize buttonSize = btn->size();
//         QPixmap scaledPixmap = cardPixmap.scaled(buttonSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

//         btn->setIcon(QIcon(scaledPixmap));
//         btn->setIconSize(buttonSize);
//         btn->setEnabled(m_gameControlsEnabled);
//         btn->setVisible(true);

//         qDebug() << "Set requested card image:" << cardName << "at index:" << index;
//     } else {
//         qWarning() << "Failed to load card image:" << cardName;
//         btn->setText(cardName);
//         btn->setEnabled(m_gameControlsEnabled);
//         btn->setVisible(true);
//     }
// }

// void GameUI::setSelectedCardImage(int index, const QString& cardName)
// {
//     QPushButton* btn = getSelectedCardButton(index);
//     if(!btn || !isValidCardName(cardName)) return;

//     QPixmap cardPixmap = loadCardImage(cardName);
//     if(!cardPixmap.isNull()) {
//         QSize buttonSize = btn->size();
//         QPixmap scaledPixmap = cardPixmap.scaled(buttonSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

//         btn->setIcon(QIcon(scaledPixmap));
//         btn->setIconSize(buttonSize);
//         btn->setEnabled(false);
//         btn->setVisible(true);

//         qDebug() << "Set selected card image:" << cardName << "at index:" << index;
//     } else {
//         qWarning() << "Failed to load card image:" << cardName;
//         btn->setText(cardName);
//         btn->setEnabled(false);
//         btn->setVisible(true);
//     }
// }

// QString GameUI::getCardImagePath(const QString& cardName)
// {
//     if(!isValidCardName(cardName)) return QString();
//     return QString(":/cards/cards/%1.JPG").arg(cardName);
// }

// bool GameUI::isValidCardName(const QString& cardName)
// {
//     if(cardName.isEmpty()) return false;
//     QStringList parts = cardName.split('-');
//     if(parts.size() != 2) return false;
//     QString unit = parts[0].toLower();
//     QString rank = parts[1].toLower();
//     QStringList validUnits = {"Gold", "Diamond", "Dollar", "Coin"};
//     if(!validUnits.contains(unit)) return false;
//     QStringList validRanks = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Soldier", "Queen", "King", "Bitcoin"};
//     if(!validRanks.contains(rank)) return false;
//     return true;
// }

// QPixmap GameUI::loadCardImage(const QString& cardName)
// {
//     QString imagePath = getCardImagePath(cardName);
//     QPixmap pixmap(imagePath);
//     if(pixmap.isNull()) {
//         qWarning() << "Could not load image from path:" << imagePath;
//     }
//     return pixmap;
// }

// QPushButton* GameUI::getRequestedCardButton(int index)
// {
//     switch(index) {
//     case 0: return ui->requestedCardButton1;
//     case 1: return ui->requestedCardButton2;
//     case 2: return ui->requestedCardButton3;
//     case 3: return ui->requestedCardButton4_2;
//     case 4: return ui->requestedCardButton5_2;
//     case 5: return ui->requestedCardButton6;
//     case 6: return ui->requestedCardButton7;
//     default: return nullptr;
//     }
// }

// QPushButton* GameUI::getSelectedCardButton(int index)
// {
//     switch(index) {
//     case 0: return ui->selectedCardButton1;
//     case 1: return ui->selectedCardButton2;
//     case 2: return ui->selectedCardButton3;
//     case 3: return ui->selectedCardButton4;
//     case 4: return ui->selectedCardButton5;
//     default: return nullptr;
//     }
// }

// void GameUI::clearRequestedCards()
// {
//     for(int i = 0; i < 7; i++) {
//         QPushButton* btn = getRequestedCardButton(i);
//         if(btn) {
//             btn->setIcon(QIcon());
//             btn->setText("");
//             btn->setVisible(false);
//         }
//     }
// }

// void GameUI::clearSelectedCards()
// {
//     for(int i = 0; i < 5; i++) {
//         QPushButton* btn = getSelectedCardButton(i);
//         if(btn) {
//             btn->setIcon(QIcon());
//             btn->setText("");
//             btn->setVisible(false);
//         }
//     }
// }

// void GameUI::onRequestedCard1Clicked()
// {
//     if(m_currentRequestedCards.size() > 0) {
//         QString cardName = m_currentRequestedCards[0];
//         sendCardRequest(cardName);
//         emit cardRequested(cardName);
//     }
// }

// void GameUI::onRequestedCard2Clicked()
// {
//     if(m_currentRequestedCards.size() > 1) {
//         QString cardName = m_currentRequestedCards[1];
//         sendCardRequest(cardName);
//         emit cardRequested(cardName);
//     }
// }

// void GameUI::onRequestedCard3Clicked()
// {
//     if(m_currentRequestedCards.size() > 2) {
//         QString cardName = m_currentRequestedCards[2];
//         sendCardRequest(cardName);
//         emit cardRequested(cardName);
//     }
// }

// void GameUI::onRequestedCard4Clicked()
// {
//     if(m_currentRequestedCards.size() > 3) {
//         QString cardName = m_currentRequestedCards[3];
//         sendCardRequest(cardName);
//         emit cardRequested(cardName);
//     }
// }

// void GameUI::onRequestedCard5Clicked()
// {
//     if(m_currentRequestedCards.size() > 4) {
//         QString cardName = m_currentRequestedCards[4];
//         sendCardRequest(cardName);
//         emit cardRequested(cardName);
//     }
// }

// void GameUI::onRequestedCard6Clicked()
// {
//     if(m_currentRequestedCards.size() > 5) {
//         QString cardName = m_currentRequestedCards[5];
//         sendCardRequest(cardName);
//         emit cardRequested(cardName);
//     }
// }

// void GameUI::onRequestedCard7Clicked()
// {
//     if(m_currentRequestedCards.size() > 6) {
//         QString cardName = m_currentRequestedCards[6];
//         sendCardRequest(cardName);
//         emit cardRequested(cardName);
//     }
// }

// void GameUI::onSelectedCard1Clicked() { qDebug() << "Selected card 1 clicked (display only)"; }
// void GameUI::onSelectedCard2Clicked() { qDebug() << "Selected card 2 clicked (display only)"; }
// void GameUI::onSelectedCard3Clicked() { qDebug() << "Selected card 3 clicked (display only)"; }
// void GameUI::onSelectedCard4Clicked() { qDebug() << "Selected card 4 clicked (display only)"; }
// void GameUI::onSelectedCard5Clicked() { qDebug() << "Selected card 5 clicked (display only)"; }

// void GameUI::setTimer(int seconds)
// {
//     m_remainingTime = seconds;
//     ui->timerlabel->setText(QString::number(seconds));
// }

// void GameUI::startTimer()
// {
//     m_gameTimer->start(1000);
// }

// void GameUI::stopTimer()
// {
//     m_gameTimer->stop();
// }

// void GameUI::onTimerTick()
// {
//     m_remainingTime--;
//     ui->timerlabel->setText(QString::number(m_remainingTime));

//     if(m_remainingTime <= 0) {
//         m_gameTimer->stop();
//         sendGameAction("timeout");
//     }
// }

// void GameUI::enableGameControls(bool enabled)
// {
//     m_gameControlsEnabled = enabled;

//     for(int i = 0; i < 7; i++) {
//         QPushButton* btn = getRequestedCardButton(i);
//         if(btn && btn->isVisible()) {
//             btn->setEnabled(enabled);
//         }
//     }

//     ui->stopButton->setEnabled(enabled);
//     ui->exitButton->setEnabled(enabled);
// }

// void GameUI::resetGameState()
// {
//     clearRequestedCards();
//     clearSelectedCards();
//     m_currentRequestedCards.clear();
//     m_currentSelectedCards.clear();
//     setTimer(0);
//     stopTimer();
//     enableGameControls(true);
//     ui->resumeButton->setEnabled(false);
// }

// // void GameUI::onStopClicked()
// // {
// //     sendGameAction("stop");
// //     ui->stopButton->setEnabled(false);
// //     ui->resumeButton->setEnabled(true);
// //     stopTimer();
// //     if (m_stopUsageCount >= 2) return;

// //     if (!m_gameIsStopped) {
// //         m_stopUsageCount++;
// //         m_gameIsStopped = true;
// //         //sendStopRequest();
// //         startTimer();
// //         //updateStopButtonState();
// //     } else {
// //         m_gameIsStopped = false;
// //         //sendResumeRequest();
// //         stopTimer();
// //         //updateStopButtonState();
// //     }
// // }

// void GameUI::onStopClicked() {
//     if (!m_gameIsStopped) {
//         // اگر بازی متوقف نشده - STOP
//         if (m_stopUsageCount >= 2) {
//             return; // نمی‌تواند بیشتر استفاده کند
//         }

//         m_stopUsageCount++;
//         m_gameIsStopped = true;
//         m_stopTimeRemaining = 30;

//         sendStopRequest();
//         startStopTimer();
//         updateStopButtonState(); // تغییر متن به "Resume"

//     } else {
//         // اگر بازی متوقف شده - RESUME
//         m_gameIsStopped = false;
//         m_stopTimer->stop();

//         sendResumeRequest();
//         updateStopButtonState(); // تغییر متن به "Stop"
//     }
// }


// void GameUI::onResumeClicked()
// {
//     sendGameAction("resume");
//     ui->stopButton->setEnabled(true);
//     ui->resumeButton->setEnabled(false);
//     startTimer();
// }

// void GameUI::onExitClicked()
// {
//     QMessageBox::StandardButton reply = QMessageBox::question(
//         this,"exit","do you want to exit?",
//         QMessageBox::Yes | QMessageBox::No
//         );

//     if(reply == QMessageBox::Yes) {
//         sendGameAction("exit");
//         emit returnToMenu();
//     }
// }

// void GameUI::sendCardRequest(const QString& cardName)
// {
//     if(!m_socketHandler) return;

//     QJsonObject message;
//     QJsonDocument doc(message);
//     QString strMsg = QString::fromUtf8(doc.toJson(QJsonDocument::Compact));
//     m_socketHandler->sendMessage(strMsg);


//     //m_socketHandler->sendMessage(message);
//     qDebug() << "Sent card request:" << cardName;
// }

// void GameUI::sendGameAction(const QString& action)
// {
//     if(!m_socketHandler) return;

//     QJsonObject message;
//     QJsonDocument doc(message);
//     QString strMsg = QString::fromUtf8(doc.toJson(QJsonDocument::Compact));
//     m_socketHandler->sendMessage(strMsg);


//     //m_socketHandler->sendMessage(message);
//     qDebug() << "Sent game action:" << action;
// }

// void GameUI::onServerMessageReceived(const QJsonObject& message)
// {
//     QString type = message["type"].toString();
//     qDebug() << "Received server message:" << type;

//     if(type == "requested_cards") {
//         QJsonArray cardsArray = message["cards"].toArray();
//         QStringList cardsList;
//         for(const auto& card : cardsArray) {
//             cardsList.append(card.toString());
//         }
//         updateRequestedCards(cardsList);
//     }
//     else if(type == "selected_cards") {
//         QJsonArray cardsArray = message["cards"].toArray();
//         QStringList cardsList;
//         for(const auto& card : cardsArray) {
//             cardsList.append(card.toString());
//         }
//         updateSelectedCards(cardsList);
//     }
//     else if(type == "timer") {
//         int seconds = message["seconds"].toInt();
//         setTimer(seconds);
//         startTimer();
//     }
//     else if(type == "game_control") {
//         bool enabled = message["enabled"].toBool();
//         enableGameControls(enabled);
//     }
// }

// void GameUI::startStopTimer() {
//     m_stopTimer->start(1000); // هر 1 ثانیه
// }

// void GameUI::onStopTimerTick() {
//     m_stopTimeRemaining--;

//     // نمایش تایمر در UI
//     ui->stopButton->setText(QString("Resume (%1)").arg(m_stopTimeRemaining));

//     if (m_stopTimeRemaining <= 0) {
//         onStopTimeExpired();
//     }
// }

// void GameUI::onStopTimeExpired() {
//     m_stopTimer->stop();

//     // ارسال پیام timeout به server
//     sendStopTimeoutRequest();

//     // بازی تمام شد
//     QMessageBox::warning(this, "بازی تمام شد", "زمان برگشت شما به پایان رسید!");
//     emit returnToMenu();
// }

// // اضافه کردن به gameUI.cpp:

// void GameUI::sendStopRequest() {
//     if (!m_socketHandler) {
//         qWarning() << "SocketHandler is null!";
//         return;
//     }

//     QJsonObject message;
//     message["action"] = "stop_game";
//     message["usage_count"] = m_stopUsageCount;

//     QJsonDocument doc(message);
//     QString jsonString = doc.toJson(QJsonDocument::Compact);

//     m_socketHandler->sendMessage(jsonString);

//     qDebug() << "Stop request sent:" << jsonString;
// }

// void GameUI::sendResumeRequest() {
//     if (!m_socketHandler) {
//         qWarning() << "SocketHandler is null!";
//         return;
//     }

//     QJsonObject message;
//     message["action"] = "resume_game";

//     QJsonDocument doc(message);
//     QString jsonString = doc.toJson(QJsonDocument::Compact);

//     m_socketHandler->sendMessage(jsonString);

//     qDebug() << "Resume request sent:" << jsonString;
// }

// void GameUI::sendStopTimeoutRequest() {
//     if (!m_socketHandler) {
//         qWarning() << "SocketHandler is null!";
//         return;
//     }

//     QJsonObject message;
//     message["action"] = "stop_timeout";
//     message["reason"] = "player_did_not_return";

//     QJsonDocument doc(message);
//     QString jsonString = doc.toJson(QJsonDocument::Compact);

//     m_socketHandler->sendMessage(jsonString);

//     qDebug() << "Stop timeout request sent:" << jsonString;
// }

// void GameUI::updateStopButtonState() {
//     if (!ui || !ui->stopButton) {
//         qWarning() << "Stop button is null!";
//         return;
//     }

//     if (m_gameIsStopped) {
//         if (m_stopTimeRemaining > 0) {
//             ui->stopButton->setText(QString("Resume (%1s)").arg(m_stopTimeRemaining));
//         } else {
//             ui->stopButton->setText("Resume");
//         }
//     } else {
//         if (m_stopUsageCount >= 2) {
//             ui->stopButton->setText("Stop (0/2)");
//             ui->stopButton->setEnabled(false);
//         } else {
//             ui->stopButton->setText(QString("Stop (%1/2)").arg(2 - m_stopUsageCount));
//             ui->stopButton->setEnabled(true);
//         }
//     }
// }
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
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
}

void GameUI::connectSignals()
{
    connect(ui->requestedCardButton1, &QPushButton::clicked, this, &GameUI::onRequestedCard1Clicked);
    connect(ui->requestedCardButton2, &QPushButton::clicked, this, &GameUI::onRequestedCard2Clicked);
    connect(ui->requestedCardButton3, &QPushButton::clicked, this, &GameUI::onRequestedCard3Clicked);
    connect(ui->requestedCardButton5_2, &QPushButton::clicked, this, &GameUI::onRequestedCard4Clicked);
    connect(ui->requestedCardButton6, &QPushButton::clicked, this, &GameUI::onRequestedCard5Clicked);
    connect(ui->requestedCardButton4_2, &QPushButton::clicked, this, &GameUI::onRequestedCard6Clicked);
    connect(ui->requestedCardButton7, &QPushButton::clicked, this, &GameUI::onRequestedCard7Clicked);
    connect(ui->selectedCardButton3, &QPushButton::clicked, this, &GameUI::onSelectedCard1Clicked);
    connect(ui->selectedCardButton1, &QPushButton::clicked, this, &GameUI::onSelectedCard2Clicked);
    connect(ui->selectedCardButton2, &QPushButton::clicked, this, &GameUI::onSelectedCard3Clicked);
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

void GameUI::markCardAsSelected(int index)
{
    if (index >= 0 && index < m_currentSelectedCards.size()) {
        m_currentSelectedCards[index] = "selected";
        setSelectedCardImage(index, "selected");
        qDebug() << "Marked card at index" << index << "as selected";
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
    if (cardName == "selected") {
        return ":/cards/selected_card.png"; // Special image for selected cards
    }

    if(!isValidCardName(cardName)) return QString();
    return QString(":/cards/cards/%1.JPG").arg(cardName);
}

bool GameUI::isValidCardName(const QString& cardName)
{
    if (cardName == "selected") return true;

    if(cardName.isEmpty()) return false;
    QStringList parts = cardName.split('-');
    if(parts.size() != 2) return false;
    QString unit = parts[0].toLower();
    QString rank = parts[1].toLower();
    QStringList validUnits = {"gold", "diamond", "dollar", "coin"};
    if(!validUnits.contains(unit)) return false;
    QStringList validRanks = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "soldier", "queen", "king", "bitcoin"};
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
