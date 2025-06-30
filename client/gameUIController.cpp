#include "gameUIController.h"

// GameUIController::GameUIController(GameUI* gameUI, SocketHandler* socketHandler, QObject *parent)
//     : QObject(parent)
//     , m_gameUI(gameUI)
//     , m_socketHandler(socketHandler)
//     , m_gameTimer(new QTimer(this))
//     , m_warningTimer(new QTimer(this))
//     , m_stopTimer(new QTimer(this))
//     , m_cardSelectionTime(CARD_SELECTION_TIME)
//     , m_warningTime(WARNING_TIME)
//     , m_stopTime(STOP_TIME)
//     , m_randomSelectionCount(0)
//     , m_stopUsageCount(0)
//     , m_gameActive(false)
//     , m_gameStopped(false)
//     , m_waitingForCards(false)
//     , m_inWarningMode(false)
//     , m_isMyTurn(false)
// {
//     setupConnections();
//     resetGameState();
// }

GameUIController::GameUIController(GameUI* gameUI, SocketHandler* socketHandler, QObject *parent)
    : QObject(parent)
    , m_gameUI(gameUI)
    , m_socketHandler(socketHandler)
    , m_gameTimer(new QTimer(this))
    , m_warningTimer(new QTimer(this))
    , m_stopTimer(new QTimer(this))
    , m_cardSelectionTime(CARD_SELECTION_TIME)
    , m_warningTimeLeft(WARNING_TIME)
    , m_stopTimeLeft(STOP_TIME)
    , m_remainingCardTime(CARD_SELECTION_TIME)
    , m_remainingWarningTime(WARNING_TIME)
    , m_remainingStopTime(STOP_TIME)
    , m_randomSelectCount(0)
    , m_stopCount(0)
    , m_isGameActive(false)
    , m_isPuased(false)
    , m_isMyTurn(false)
    , m_playerId("")
    /*, m_warningTime(WARNING_TIME)
    , m_stopTime(STOP_TIME)*/
    , m_waitingForCards(false)
    , m_inWarningMode(false)

{
    setupConnections();
    resetGameState();
}




GameUIController::~GameUIController()
{
    stopAllTimers();
}

void GameUIController::setupConnections()
{
    connect(m_gameUI, &GameUI::cardSelected, this, &GameUIController::onCardSelected);
    connect(m_gameUI, &GameUI::selectedCardClicked, this, &GameUIController::onSelectedCardClicked);
    connect(m_gameUI, &GameUI::stopRequested, this, &GameUIController::onStopRequested);
    connect(m_gameUI, &GameUI::resumeRequested, this, &GameUIController::onResumeRequested);
    connect(m_gameUI, &GameUI::exitRequested, this, &GameUIController::onExitRequested);
    connect(m_socketHandler, &SocketHandler::messageReceived, this, &GameUIController::onServerMessageReceived);
    connect(m_gameTimer, &QTimer::timeout, this, &GameUIController::onGameTimerTick);
    connect(m_warningTimer, &QTimer::timeout, this, &GameUIController::onWarningTimerTick);
    connect(m_stopTimer, &QTimer::timeout, this, &GameUIController::onStopTimerTick);

    m_gameTimer->setSingleShot(false);
    m_warningTimer->setSingleShot(false);
    m_stopTimer->setSingleShot(false);
}

// void GameUIController::resetGameState()
// {
//     stopAllTimers();

//     m_currentRequestedCards.clear();
//     m_currentSelectedCards.clear();
//     m_currentPlayer.clear();
//     m_gameState = "idle";

//     m_remainingCardTime = m_cardSelectionTime;
//     m_remainingWarningTime = m_warningTime;
//     m_remainingStopTime = m_stopTime;

//     m_randomSelectCount = 0;
//     m_stopUsageCount = 0;

//     m_isGameActive = false;
//     m_isPuased = false;
//     m_waitingForCards = false;
//     m_inWarningMode = false;
//     m_isMyTurn = false;

//     m_gameUI->resetGameUI();
//     m_gameUI->enableGameControls(true);
// }

void GameUIController::resetGameState()
{
    stopAllTimers();

    m_currentRequestedCards.clear();
    m_currentSelectedCards.clear();
    m_currentPlayer.clear();
    m_gameState = "idle";

    m_remainingCardTime = m_cardSelectionTime;
    m_remainingWarningTime = m_warningTime;
    m_remainingStopTime = m_stopTime;

    m_randomSelectCount = 0;
    m_stopCount = 0;

    m_isGameActive = false;
    m_isPuased = false;
    m_waitingForCards = false;
    m_inWarningMode = false;
    m_isMyTurn = false;

    m_gameUI->resetGameUI();
    m_gameUI->enableGameControls(true);
}


void GameUIController::sendToServer(const QString& message)
{
    if (m_socketHandler) {
        m_socketHandler->sendMessage(message);
        qDebug() << "Sent to server:" << message;
    } else {
        qWarning() << "SocketHandler is null!";
    }
}


void GameUIController::startNewGame()
{
    qDebug() << "Starting new game...";
    resetGameState();
    m_isGameActive = true;
    m_gameState = "playing";

    sendToServer("game_start");
}

void GameUIController::stopGame()
{
    if (!m_isGameActive) return;

    qDebug() << "Stopping game...";
    handleStopRequest();
}

void GameUIController::resumeGame()
{
    if (!m_isPuased) return;

    qDebug() << "Resuming game...";
    handleResumeRequest();
}

void GameUIController::exitGame()
{
    qDebug() << "Exiting game...";
    stopAllTimers();
    sendExitRequest();
    emit returnToMenu();
}

void GameUIController::updateDisplayedCards(const QStringList& requestedCards, const QStringList& selectedCards)
{
    m_currentRequestedCards = requestedCards;
    m_currentSelectedCards = selectedCards;

    m_gameUI->updateRequestedCards(requestedCards);
    m_gameUI->updateSelectedCards(selectedCards);

    if (m_isMyTurn && !requestedCards.isEmpty()) {
        startCardSelectionTimer();
    }
}

// void GameUIController::onCardSelected(int index, const QString& cardName)
// {
//     if (!m_gameActive || m_gameStopped || !m_isMyTurn) {
//         qDebug() << "Card selection ignored - game not active or not my turn";
//         return;
//     }

//     qDebug() << "Card selected:" << cardName << "at index:" << index;
//     processCardSelection(index, cardName);
// }

// void GameUIController::onSelectedCardClicked(int index)
// {
//     qDebug() << "Selected card clicked at index:" << index << "(display only)";
// }

void GameUIController::onCardSelected(int cardIndex, const QString& cardValue)
{
    if (!m_isGameActive || m_isPuased || !m_isMyTurn) {
        return;
    }

    stopAllTimers();

    QJsonObject message;
    message["type"] = "cardSelection";
    message["cardIndex"] = cardIndex;
    message["cardValue"] = cardValue;
    message["playerId"] = m_playerId;

    QJsonDocument doc(message);
    m_socketHandler->sendMessage(doc.toJson(QJsonDocument::Compact));
    m_isMyTurn = false;
    if (m_gameUI) {
        m_gameUI->updateGameStatus("Waiting for other players...");
    }
}

void GameUIController::onStopRequested()
{
    if (!m_isGameActive || m_isPuased) {
        qDebug() << "Stop request ignored-game not active or already stopped";
        return;
    }

    qDebug() << "Stop requested by user";
    handleStopRequest();
}

void GameUIController::onResumeRequested()
{
    if (!m_isPuased) {
        qDebug() << "Resume request ignored-game not stopped";
        return;
    }

    qDebug() << "▶️ Resume requested by user";
    handleResumeRequest();
}

void GameUIController::onExitRequested()
{
    qDebug() << "Exit requested by user";
    exitGame();
}

void GameUIController::processCardSelection(int index, const QString& cardName)
{
    if (index < 0 || index >= m_currentRequestedCards.size()) {
        qWarning() << "Invalid card index:" << index;
        return;
    }
    stopAllTimers();
    m_inWarningMode = false;
    m_gameUI->markCardAsSelected(index);
    sendCardSelectionToServer(cardName);
    m_gameUI->enableGameControls(false);
    m_isMyTurn = false;

    qDebug() << "Card selection processed successfully:" << cardName;
}

void GameUIController::performRandomCardSelection()
{
    if (m_currentRequestedCards.isEmpty()) {
        qWarning() << "No cards available for random selection";
        return;
    }
    int randomIndex = QRandomGenerator::global()->bounded(m_currentRequestedCards.size());
    QString randomCard = m_currentRequestedCards[randomIndex];

    qDebug() << "Random card selected:" << randomCard << "at index:" << randomIndex;
    m_randomSelectCount++;
    processCardSelection(randomIndex, randomCard);
    sendRandomSelectionNotification();
    checkRandomSelectionLimit();
}

void GameUIController::sendCardSelectionToServer(const QString& cardName)
{
    QJsonObject data;
    data["card"] = cardName;
    data["timestamp"] = QDateTime::currentMSecsSinceEpoch();

    sendToServer("card_selected", data);
}

void GameUIController::startCardSelectionTimer()
{
    qDebug() << "Starting card selection timer (20s)";

    m_remainingCardTime = m_cardSelectionTime;
    m_gameUI->setTimerDisplay(m_remainingCardTime);
    m_gameTimer->start(1000);
}

void GameUIController::startWarningTimer()
{
    qDebug() << "starting warning timer (10s)";

    m_inWarningMode = true;
    m_remainingWarningTime = m_warningTime;
    m_gameUI->setTimerDisplay(m_remainingWarningTime);
    m_warningTimer->start(1000);

    QMessageBox::warning(m_gameUI, "warning", "You have 10 seconds to choose a card, otherwise, a card will be chosen randomly after this time.");
}

void GameUIController::startStopTimer()
{
    qDebug() << "Starting stop timer(30s)";
    m_remainingStopTime = m_stopTimeLeft;
    m_stopTimer->start(1000);
    QString buttonText = QString("Resume (%1s)").arg(m_remainingStopTime);
    m_gameUI->updateStopButtonAppearance(buttonText, true);
}

void GameUIController::stopAllTimers()
{
    m_gameTimer->stop();
    m_warningTimer->stop();
    m_stopTimer->stop();
}

void GameUIController::onGameTimerTick()
{
    m_remainingCardTime--;
    m_gameUI->setTimerDisplay(m_remainingCardTime);
    if (m_remainingCardTime <= 0) {
        m_gameTimer->stop();
        onCardSelectionTimeout();
    }
}

void GameUIController::onWarningTimerTick()
{
    m_remainingWarningTime--;
    m_gameUI->setTimerDisplay(m_remainingWarningTime);
    if (m_remainingWarningTime <= 0) {
        m_warningTimer->stop();
        onWarningTimeout();
    }
}

void GameUIController::onStopTimerTick()
{
    m_remainingStopTime--;

    QString buttonText = QString("Resume (%1s)").arg(m_remainingStopTime);
    m_gameUI->updateStopButtonAppearance(buttonText, true);

    if (m_remainingStopTime <= 0) {
        m_stopTimer->stop();
        onStopTimerTick();
    }
}

void GameUIController::onCardSelectionTimeout()
{
    qDebug() << "Card selection timeout(20s)-Starting warning timer";
    startWarningTimer();
}

void GameUIController::onWarningTimeout()
{
    qDebug() << "Warning timeout (10s) - Performing random selection";
    performRandomCardSelection();
}

void GameUIController::onStopTimeout()
{
    qDebug() << "Stop timeout(30s)-Game ending";
    handleStopTimeoutExpired();
}

void GameUIController::handleStopRequest()
{
    if (m_stopCount >= MAX_STOP_USAGE) {
        qWarning() << "Stop usage limit reached";
        return;
    }

    m_stopCount++;
    m_isPuased = true;
    m_gameState = "stopped";
    m_gameTimer->stop();
    m_warningTimer->stop();
    startStopTimer();
    m_gameUI->enableGameControls(false);
    sendStopRequest();
    qDebug() << "Game stopped. Usage count:" << m_stopCount;
}

void GameUIController::handleResumeRequest()
{
    m_isPuased = false;
    m_gameState = "playing";
    m_stopTimer->stop();
    m_gameUI->enableGameControls(true);
    m_gameUI->updateStopButtonAppearance("Stop", true);
    if (m_isMyTurn) {
        if (m_inWarningMode) {
            startWarningTimer();
        } else {
            startCardSelectionTimer();
        }
    }
    sendResumeRequest();

    qDebug() << "Game resumed";
}

void GameUIController::handleStopFromServer()
{
    qDebug() << "Stop received from server";
    stopAllTimers();
    m_gameUI->enableGameControls(false);
    m_gameUI->updateStopButtonAppearance("Waiting...", false);

    m_isPuased = true;
    m_gameState = "stopped";
}

void GameUIController::handleResumeFromServer()
{
    qDebug() << "Resume received from server";
    m_isPuased = false;
    m_gameState = "playing";
    m_gameUI->enableGameControls(true);
    m_gameUI->updateStopButtonAppearance("Stop", true);
    if (m_isMyTurn) {
        startCardSelectionTimer();
    }
}

void GameUIController::checkRandomSelectionLimit()
{
    if (m_randomSelectCount >= MAX_RANDOM_SELECTIONS) {
        qDebug() << "Random selection limit reached:" << m_randomSelectCount;
        QJsonObject data;
        data["reason"] = "random_selection_limit";
        data["count"] = m_randomSelectCount;
        sendToServer("game_violation", data);

        returnAllPlayersToMenu("the player did not choose cards to time.");
    }
}

void GameUIController::checkStopUsageLimit()
{
    if (m_stopCount >= MAX_STOP_USAGE) {
        qDebug() << "Stop usage limit reached:" << m_stopCount;
        QJsonObject data;
        data["reason"] = "stop_usage_limit";
        data["count"] = m_stopCount;
        sendToServer("game_violation", data);
        returnAllPlayersToMenu("the player stopped the game 2 times.");
    }
}

void GameUIController::handleStopTimeoutExpired()
{
    qDebug() << "Stop timeout expired - Game ending";

    QJsonObject data;
    data["reason"] = "stop_timeout";
    data["stop_count"] = m_stopCount;

    sendToServer("stop_timeout_expired", data);

    returnAllPlayersToMenu("the time to get back into the game is over.");
}

void GameUIController::sendToServer(const QString& action, const QJsonObject& data)
{
    QJsonObject message;
    message["action"] = action;
    message["timestamp"] = QDateTime::currentMSecsSinceEpoch();
    if (!data.isEmpty()) {
        message["data"] = data;
    }
    QJsonDocument doc(message);
    m_socketHandler->sendMessage(doc.toJson(QJsonDocument::Compact));
}

void GameUIController::sendStopRequest()
{
    QJsonObject data;
    data["stop_count"] = m_stopCount;
    sendToServer("game_stop", data);
}

void GameUIController::sendResumeRequest()
{
    sendToServer("game_resume");
}

void GameUIController::sendRandomSelectionNotification()
{
    QJsonObject data;
    data["random_count"] = m_randomSelectCount;
    sendToServer("random_selection", data);
}

void GameUIController::sendStopTimeoutNotification()
{
    QJsonObject data;
    data["reason"] = "stop_timeout";
    sendToServer("timeout_violation", data);
}

void GameUIController::sendExitRequest()
{
    sendToServer("game_exit");
}

void GameUIController::onServerMessageReceived(const QString& message)
{
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8(), &error);

    if (error.error != QJsonParseError::NoError) {
        qWarning() << "JSON parse error:" << error.errorString();
        return;
    }

    QJsonObject obj = doc.object();
    handleServerMessage(obj);
}

void GameUIController::handleServerMessage(const QJsonObject& message)
{
    QString action = message["action"].toString();
    QJsonObject data = message["data"].toObject();

    qDebug() << "Server message:" << action;

    if (action == "cards_dealt") {
        QStringList requested = data["requested"].toVariant().toStringList();
        QStringList selected = data["selected"].toVariant().toStringList();
        QString currentPlayer = data["current_player"].toString();

        m_currentPlayer = currentPlayer;
        m_isMyTurn = (currentPlayer == m_socketHandler->getPlayerId());

        updateDisplayedCards(requested, selected);

    } else if (action == "game_stopped") {
        handleStopFromServer();

    } else if (action == "game_resumed") {
        handleResumeFromServer();

    } else if (action == "game_ended") {
        QString reason = data["reason"].toString();
        handleGameEnd(reason);

    } else if (action == "return_to_menu") {
        QString reason = data["reason"].toString();
        returnAllPlayersToMenu(reason);

    } else if (action == "player_turn") {
        QString player = data["player"].toString();
        m_isMyTurn = (player == m_socketHandler->getPlayerId());

        if (m_isMyTurn && !m_isPuased) {
            startCardSelectionTimer();
        }

    } else if (action == "game_state") {
        QString state = data["state"].toString();
        updateGameState(state);
    }
}

void GameUIController::updateGameState(const QString& state)
{
    m_gameState = state;
    qDebug() << "Game state updated:" << state;

    if (state == "finished") {
        stopAllTimers();
        m_isGameActive = false;
        emit gameFinished();
    }
}

void GameUIController::handleGameEnd(const QString& reason)
{
    qDebug() << "Game ended:" << reason;
    stopAllTimers();
    m_isGameActive= false;
    m_gameState = "finished";
    QMessageBox::information(m_gameUI, "end of game", reason);
    emit gameFinished();
}

void GameUIController::returnAllPlayersToMenu(const QString& reason)
{
    qDebug() << "Returning to menu:" << reason;

    stopAllTimers();
    m_isGameActive = false;

    QMessageBox::information(m_gameUI, "return to menu", reason);

    emit returnToMenu();
}

