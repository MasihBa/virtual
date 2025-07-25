#include "gameUIController.h"

GameUIController::GameUIController(GameUI* gameUI, SocketHandler* socketHandler, const QString username, QObject *parent)
    : QObject(parent)
    , m_gameUI(gameUI)
    , m_socketHandler(socketHandler)
    , m_username(username)
    , m_cardSelectionTimer(new QTimer(this))
    , m_warningTimer(new QTimer(this))
    , m_stopTimer(new QTimer(this))
    , m_gameState("idle")
    , m_remainingCardTime(TOTAL_CARD_TIME)
    , m_remainingWarningTime(WARNING_TIME)
    , m_remainingStopTime(STOP_TIME)
    , m_randomSelectionCount(0)
    , m_stopUsageCount(0)
    , m_isGameActive(false)
    , m_isGamePaused(false)
    //, m_isMyTurn(false)
    , m_inWarningMode(false)
    , m_stopButtonDisabled(false)
    ,m_playerUsername(username)
    ,m_savedTimerType("none")
    , m_savedRemainingTime(0)
    , m_isServerPaused(false)
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
    // UI Connections
    connect(m_gameUI, &GameUI::cardSelected, this, &GameUIController::onCardSelected);
    connect(m_gameUI, &GameUI::stopRequested, this, &GameUIController::onStopRequested);
    connect(m_gameUI, &GameUI::resumeRequested, this, &GameUIController::onResumeRequested);
    connect(m_gameUI, &GameUI::exitRequested, this, &GameUIController::onExitRequested);

    // Network Connections
    disconnect(m_socketHandler, &SocketHandler::messageReceived, nullptr, nullptr);
    connect(m_socketHandler, &SocketHandler::messageReceived, this, &GameUIController::onServerMessageReceived);


    // Timer Connections
    connect(m_cardSelectionTimer, &QTimer::timeout, this, &GameUIController::onCardSelectionTimerTick);
    connect(m_warningTimer, &QTimer::timeout, this, &GameUIController::onWarningTimerTick);
    connect(m_stopTimer, &QTimer::timeout, this, &GameUIController::onStopTimerTick);

    // Timer Settings
    m_cardSelectionTimer->setSingleShot(false);
    m_warningTimer->setSingleShot(false);
    m_stopTimer->setSingleShot(false);

    // manage chat
    connect(m_gameUI, &GameUI::chatMessageSent, this, &GameUIController::onChatMessageSent);
}

void GameUIController::resetGameState()
{
    qDebug() << "Resetting game state...";

    stopAllTimers();

    // Reset Game Data
    m_currentRequestedCards.clear();
    m_currentSelectedCards.clear();
    m_gameState = "idle";

    // Reset Timers
    m_remainingCardTime = TOTAL_CARD_TIME;
    m_remainingWarningTime = WARNING_TIME;
    m_remainingStopTime = STOP_TIME;

    // Reset Counters
    m_randomSelectionCount = 0;
    m_stopUsageCount = 0;

    // Reset Flags
    m_isGameActive = false;
    m_isGamePaused = false;
    //m_isMyTurn = false;
    m_inWarningMode = false;
    m_stopButtonDisabled = false;

    // the stop variables
    m_isServerPaused = false;
    m_savedTimerType = "none";
    m_savedRemainingTime = 0;

    // Reset UI
    m_gameUI->resetGameUI();
    m_gameUI->enableGameControls(true);
    m_gameUI->updateStopButtonAppearance("Stop", true);
    m_gameUI->updateGameStatus("Ready to start...");
}

//  ==================== GAME CONTROL METHODS ====================

void GameUIController::startNewGame()
{
    qDebug() << " Starting new game...";

    resetGameState();
    m_isGameActive = true;
    m_gameState = "playing";

    m_gameUI->updateGameStatus("Game started! Waiting for your turn...");
    //sendToServer("game_start");//..................................................................
}

void GameUIController::stopGame()
{
    if (!m_isGameActive || m_isGamePaused || m_stopButtonDisabled) {
        qDebug() << "Stop request ignored - conditions not met";
        return;
    }

    qDebug() << "Stopping game...";
    handleStopRequest();
}

void GameUIController::resumeGame()
{
    if (!m_isGamePaused) {
        qDebug() << "Resume request ignored - game not paused";
        return;
    }

    qDebug() << "Resuming game...";
    handleResumeRequest();
}

void GameUIController::exitGame()
{
    qDebug() << "Exiting game...";

    stopAllTimers();
    sendToServer("exit_game");
    emit returnToMenu();
}

// ==================== UI EVENT HANDLERS ====================

void GameUIController::onCardSelected(int index, const QString cardName)
{
    if (!m_isGameActive || m_isGamePaused) {
        qDebug() << "Card selection ignored - game conditions not met";
        return;
    }

    if (m_currentRequestedCards.isEmpty()) {
        qDebug() << "No cards available for selection";
        return;
    }

    if (index < 0 || index >= m_currentRequestedCards.size()) {
        qWarning() << "Invalid card index:" << index << "/ Available:" << m_currentRequestedCards.size();
        return;
    }
    // the if to check the pause state
    if (m_isServerPaused) {
        qDebug() << "Card selection ignored - Server has paused the game";
        return;
    }

    // the if to check the pause state
    if (!m_isGameActive || m_isGamePaused) {
        qDebug() << "Card selection ignored - Game not active or paused";
        return;
    }

    qDebug() << "Card selected:" << cardName << "at index:" << index;
    processCardSelection(index, cardName);
}

void GameUIController::onStopRequested()
{
    if (m_stopButtonDisabled) {
        qDebug() << "Stop button is disabled";
        return;
    }

    stopGame();
}

void GameUIController::onResumeRequested()
{
    resumeGame();
}

void GameUIController::onExitRequested()
{
    exitGame();
}

// ==================== TIMER EVENT HANDLERS ====================

void GameUIController::onCardSelectionTimerTick()
{
    m_remainingCardTime--;
    m_gameUI->setTimerDisplay(m_remainingCardTime);

    qDebug() << "Card selection time remaining:" << m_remainingCardTime;

    // warning is started after 20 seconds
    if (m_remainingCardTime <= WARNING_TIME) {
        m_cardSelectionTimer->stop();
        onCardSelectionTimeout();
    }

    if (m_remainingCardTime <= 0) {
        m_cardSelectionTimer->stop();
        onWarningTimeout(); //for manage random selection
    }
}

void GameUIController::onWarningTimerTick()
{
    m_remainingWarningTime--;
    m_gameUI->setTimerDisplay(m_remainingWarningTime);

    qDebug() << "Warning time remaining:" << m_remainingWarningTime;

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

    qDebug() << "Stop time remaining:" << m_remainingStopTime;

    if (m_remainingStopTime <= 0) {
        m_stopTimer->stop();
        onStopTimeout();
    }
}

// ==================== TIMEOUT HANDLERS ====================

void GameUIController::onCardSelectionTimeout()
{
    qDebug() << "Card selection timeout (20s) - Starting warning period";
    m_inWarningMode = true;
    m_remainingWarningTime = WARNING_TIME;
    QMessageBox::warning(m_gameUI, "Warning", QString("You have %1 seconds to choose a card!\nOtherwise a card will be selected randomly.").arg(WARNING_TIME));
    m_gameUI->updateGameStatus("WARNING: Choose a card quickly!");

    startWarningTimer();
}

void GameUIController::onWarningTimeout()
{
    qDebug() << "Warning timeout (10s) - Performing random selection";

    performRandomCardSelection();
    sendNoSelectionWarning(); //8;username
    checkRandomSelectionLimit();
}

void GameUIController::onStopTimeout()
{
    qDebug() << "Stop timeout (30s) - Sending timeout warning to server";

    sendStopTimeoutWarning(); // 9;username
    m_gameUI->updateGameStatus("Stop time expired! Game may end soon...");
}

// ==================== CARD SELECTION LOGIC ====================

void GameUIController::processCardSelection(int index, const QString cardName)
{
    if (index < 0 || index >= m_currentRequestedCards.size()) {
        qWarning() << "Invalid card index:" << index;
        return;
    }

    qDebug() << "Processing card selection:" << cardName;
    stopAllTimers();
    m_currentSelectedCards.append(cardName);
    m_gameUI->updateSelectedCards(m_currentSelectedCards);
    // I insert above line to update the selectedCards................................................................
    // m_gameUI->markCardAsSelected(index);
    m_inWarningMode = false;

    //m_isMyTurn = false;
    m_gameUI->updateRequestedCards(QStringList());
    m_currentRequestedCards.clear();
    m_gameUI->enableGameControls(false);
    m_gameUI->updateGameStatus("Card selected! Waiting for other players...");
    sendCardSelectionToServer(cardName);
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

    m_randomSelectionCount++;
    processCardSelection(randomIndex, randomCard);

    QMessageBox::information(m_gameUI, "Random Selection", QString("Card '%1' was randomly selected for you!").arg(randomCard));
}

void GameUIController::sendCardSelectionToServer(const QString cardName)
{
    QString message = QString("7;%1;%2").arg(m_username, cardName);
    sendToServer(message);

    qDebug() << "Sent card selection to server:" << message;
}

// ==================== TIMER MANAGEMENT ====================

void GameUIController::startCardSelectionTimer()
{
    qDebug() << "Starting card selection timer (30s total)";
    m_remainingCardTime = TOTAL_CARD_TIME;
    m_gameUI->setTimerDisplay(m_remainingCardTime);
    m_cardSelectionTimer->start(1000);
}

void GameUIController::startWarningTimer()
{
    qDebug() << "Starting warning timer (10s)";

    m_remainingWarningTime = WARNING_TIME;
    m_gameUI->setTimerDisplay(m_remainingWarningTime);
    m_warningTimer->start(1000);
}

void GameUIController::startStopTimer()
{
    qDebug() << "Starting stop timer (30s)";

    m_remainingStopTime = STOP_TIME;
    QString buttonText = QString("Resume (%1s)").arg(m_remainingStopTime);
    m_gameUI->updateStopButtonAppearance(buttonText, true);
    m_stopTimer->start(1000);
}

void GameUIController::stopAllTimers()
{
    m_cardSelectionTimer->stop();
    m_warningTimer->stop();
    m_stopTimer->stop();

    qDebug() << "All timers stopped";
}

// ==================== GAME CONTROL HANDLERS ====================

void GameUIController::handleStopRequest()
{
    if (m_stopUsageCount >= 2) {
        qDebug() << "Stop usage limit reached!";
        disableStopButton();
        return;
    }
    m_stopUsageCount++;
    m_isGamePaused = true;
    m_gameState = "stopped";
    stopAllTimers();
    startStopTimer();
    m_gameUI->enableGameControls(false);
    m_gameUI->updateGameStatus("Game paused. Resume quickly!");
    sendToServer(QString("stop_game;%1").arg(m_username));
    qDebug() << "Game stopped. count:" << m_stopUsageCount;
    if (m_stopUsageCount >= 2) {
        disableStopButton();
    }
}

void GameUIController::handleResumeRequest()
{
    m_isGamePaused = false;
    m_gameState = "playing";

    m_stopTimer->stop();
    m_gameUI->enableGameControls(true);
    m_gameUI->updateStopButtonAppearance("Stop", !m_stopButtonDisabled);
    m_gameUI->updateGameStatus("Game resumed!");
    // if (m_isMyTurn) {
    //     if (m_inWarningMode) {
    //         startWarningTimer();
    //     } else {
    //         startCardSelectionTimer();
    //     }
    // }

    if (!m_currentRequestedCards.isEmpty()) {
        if (m_inWarningMode) {
            startWarningTimer();
        } else {
            startCardSelectionTimer();
        }
    }
    sendToServer(QString("resume_game;%1").arg(m_username));

    qDebug() << "Game resumed";
}

void GameUIController::handleGameFinish()
{
    qDebug() << "Game finished";

    stopAllTimers();
    m_isGameActive = false;
    m_gameState = "finished";

    m_gameUI->enableGameControls(false);
    m_gameUI->updateGameStatus("Game finished! Returning to menu...");

    QTimer::singleShot(2000, this, [this]() {
        emit returnToMenu();
    });
}

// ==================== NETWORK COMMUNICATION ====================


void GameUIController::sendToServer(const QString message)
{
    if (m_socketHandler && m_socketHandler->state() == QAbstractSocket::ConnectedState) {
        m_socketHandler->sendMessage(message);
        qDebug() << "Sent to server:" << message;
    } else if (m_socketHandler) {
        qWarning() << "Not connected to server. Attempting to reconnect...";
        m_socketHandler->connectToServer();
        m_socketHandler->sendMessage(message);
    } else {
        qWarning() << "SocketHandler is null!";
    }
}

void GameUIController::sendNoSelectionWarning()
{
    QString message = QString("8;%1").arg(m_username);
    sendToServer(message);

    qDebug() << "Sent no selection warning:" << message;
}

void GameUIController::sendStopTimeoutWarning()
{
    QString message = QString("9;%1").arg(m_username);
    sendToServer(message);

    qDebug() << "Sent stop timeout warning:" << message;
}

// ==================== GAME STATE MANAGEMENT ====================

void GameUIController::checkRandomSelectionLimit()
{
    qDebug() << "Random selection count:" << m_randomSelectionCount << "/" << MAX_RANDOM_SELECTIONS;

    if (m_randomSelectionCount >= MAX_RANDOM_SELECTIONS) {
        qDebug() << "Random selection limit reached! Game should end.";
        m_gameUI->updateGameStatus("Too many timeouts! Game may end...");
    }
}

void GameUIController::checkStopUsageLimit()
{
    qDebug() << "Stop usage count:" << m_stopUsageCount << "/" << 2;

    if (m_stopUsageCount >= 2) {
        disableStopButton();
    }
}

void GameUIController::disableStopButton()
{
    m_stopButtonDisabled = true;
    m_gameUI->updateStopButtonAppearance("Stop (Disabled)", false);

    qDebug() << "Stop button disabled permanently";
}

void GameUIController::updateGameState(const QString state)
{
    m_gameState = state;
    qDebug() << "Game state updated to:" << state;
}

// ==================== SERVER MESSAGE HANDLER ====================

void GameUIController::onServerMessageReceived(const QString message)
{
    qDebug() << "Received server message:" << message;
    handleServerMessage(message);
}


void GameUIController::handleServerMessage(const QString message)
{
    QStringList parts = message.split(";");

    QString command = parts[0];
    qDebug() << "Processing command:" << command;

    if (command == "cards_data" && parts.size() >= 8) {
        QStringList cardNames;
        for (int i = 1; i < parts.size(); i++) {
            if (!parts[i].isEmpty()) {
                cardNames.append(parts[i]);
            }
        }

        qDebug() << "Received cards from server:" << cardNames;
        m_currentRequestedCards = cardNames;
        m_gameUI->updateRequestedCards(cardNames);
        m_gameUI->updateGameStatus("Your turn! Choose a card.");
        m_gameUI->enableGameControls(true);
        startCardSelectionTimer();

    } else if (command == "10" && parts.size() >= 3) {// 10;username;text
        QString username = parts[1];
        QString chatText = parts[2];
        qDebug() << "Chat message received from" << username << ":" << chatText;

        if (username != m_playerUsername) {
            m_gameUI->displayChatMessage(username, chatText);
        }

    } else if (command == "game_finish" || command == "gamefinish") {
        // game_finish;username1;number;username2;number;username3;number;username4;number;winner

        if (parts.size() >= 10) {
            for (int i = 1; i < 9; i += 2) {
                if (i + 1 < parts.size()) {
                    QString username = parts[i];
                    QString numberStr = parts[i + 1];

                    if (username == m_playerUsername) {
                        int number = numberStr.toInt();

                        if (number == 1) {
                            QMessageBox::information(m_gameUI, "Game Result", "Winner!");
                        } else if (number == -1) {
                            QMessageBox::information(m_gameUI, "Game Result", "Loser!");
                        }

                        break;
                    }
                }
            }
        }

        handleGameFinish();

    } else if (command == "stop_received") {
        qDebug() << "Server confirmed stop request";

    } else if (command == "resume_received") {
        qDebug() << "Server confirmed resume request";

    }else if(command == "round_over"){// round_over;username1;pattern;username2;pattern;username3;pattern;username4;pattern;winner // I should show this in the in the infolabel
        // sendToServer(QString("18;0"));
        // m_currentSelectedCards.clear();
        // m_gameUI->updateSelectedCards(QStringList());
        sendToServer(QString("18;0"));
        m_currentSelectedCards.clear();
        m_gameUI->updateSelectedCards(QStringList());
        if (parts.size() >= 10) {
            QString roundInfo = "Round Results:";

            for (int i = 1; i < 9; i += 2) {
                if (i + 1 < parts.size()) {
                    QString username = parts[i];
                    QString pattern = parts[i + 1];
                    roundInfo += QString("%1: %2").arg(username, pattern);
                }
            }

            if (parts.size() >= 10) {
                QString winner = parts[9];
                roundInfo += QString("Winner: %1").arg(winner);
            }

            m_gameUI->updateGameStatus(roundInfo);

            qDebug() << "Round over info displayed:" << roundInfo;
        }
    }else if (command == "puase" || command == "stop") {
        handleServerPause();

    } else if (command == "continue" || command == "resume") {
        handleServerContinue();
    }
    else {
        qDebug() << "Unknown server command:" << command;
    }
}


// ==================== SERVER MESSAGE HANDLER ====================

void GameUIController::onChatMessageSent(const QString message)
{
    if(message.trimmed().isEmpty()) return;

    m_gameUI->displayChatMessage(m_playerUsername, message);

    sendChatMessageToServer(message);
}

void GameUIController::sendChatMessageToServer(const QString message)
{
    QString serverMessage = QString("10;%1;%2")
    .arg(m_playerUsername)
        .arg(message);

    if(m_socketHandler) {
        m_socketHandler->sendMessage(serverMessage);
        qDebug() << "Chat message sent to server:" << serverMessage;
    }
}

// ==================== SERVER PAUSE HANDLE ====================

void GameUIController::saveCurrentTimerState()
{
    m_savedTimerType = "none";
    m_savedRemainingTime = 0;

    if (m_cardSelectionTimer->isActive()) {
        m_savedTimerType = "card";
        m_savedRemainingTime = m_remainingCardTime;
    } else if (m_warningTimer->isActive()) {
        m_savedTimerType = "warning";
        m_savedRemainingTime = m_remainingWarningTime;
    } else if (m_stopTimer->isActive()) {
        m_savedTimerType = "stop";
        m_savedRemainingTime = m_remainingStopTime;
    }

    qDebug() << "Timer state saved:" << m_savedTimerType << "Time:" << m_savedRemainingTime;
}



void GameUIController::handleServerPause()
{
    qDebug() << "Server PAUSE received - Disabling all controls";

    saveCurrentTimerState();

    stopAllTimers();

    m_isServerPaused = true;

    m_gameUI->enableGameControls(false);

    m_gameUI->updateGameStatus("Game paused by server...");
}

void GameUIController::handleServerContinue()
{
    qDebug() << "Server CONTINUE received - Enabling controls";
    m_isServerPaused = false;
    m_gameUI->enableGameControls(true);
    restoreTimerState();
    m_gameUI->updateGameStatus("Game resumed!");
    m_savedTimerType = "none";
    m_savedRemainingTime = 0;
}

void GameUIController::restoreTimerState()
{
    if (m_savedTimerType == "card" && m_savedRemainingTime > 0) {
        m_remainingCardTime = m_savedRemainingTime;
        m_gameUI->setTimerDisplay(m_remainingCardTime);
        m_cardSelectionTimer->start(1000);
        qDebug() << "Card timer restored:" << m_remainingCardTime << "seconds";

    } else if (m_savedTimerType == "warning" && m_savedRemainingTime > 0) {
        m_remainingWarningTime = m_savedRemainingTime;
        m_gameUI->setTimerDisplay(m_remainingWarningTime);
        m_warningTimer->start(1000);
        m_inWarningMode = true;
        qDebug() << "Warning timer restored:" << m_remainingWarningTime << "seconds";

    } else if (m_savedTimerType == "stop" && m_savedRemainingTime > 0) {
        m_remainingStopTime = m_savedRemainingTime;
        QString buttonText = QString("Resume (%1s)").arg(m_remainingStopTime);
        m_gameUI->updateStopButtonAppearance(buttonText, true);
        m_stopTimer->start(1000);
        qDebug() << "Stop timer restored:" << m_remainingStopTime << "seconds";
    }
}

