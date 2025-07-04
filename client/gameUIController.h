// GAMEUICONTROLLER_H
#ifndef GAMEUICONTROLLER_H
#define GAMEUICONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QJsonObject>
#include <QJsonDocument>
#include <QStringList>
#include <QRandomGenerator>
#include <QDebug>
#include <QDateTime>
#include <QMessageBox>
#include "gameui.h"
#include "sockethandler.h"

class GameUIController : public QObject
{
    Q_OBJECT

public:
    explicit GameUIController(GameUI* gameUI, SocketHandler* socketHandler, const QString username, QObject *parent = nullptr);
    ~GameUIController();

    void startNewGame();
    void stopGame();
    void resumeGame();
    void exitGame();

signals:
    void gameFinished();
    void returnToMenu();
    void gameError(const QString& error);

public slots:
    // UI Events
    void onCardSelected(int index, const QString cardName);
    void onStopRequested();
    void onResumeRequested();
    void onExitRequested();

    // Network Events
    void onServerMessageReceived(const QString message);

    // Timer Events
    void onCardSelectionTimerTick();//30 second to select card
    void onWarningTimerTick();// 10 second- for the end of the 30 second time to select a card
    void onStopTimerTick();// for stop the game by user

    // Timeout Events
    void onCardSelectionTimeout();//warning after 20 second
    void onWarningTimeout();// random selection after 10 seconds
    void onStopTimeout();// start stop timer after 30 second

    // manage chat
    void onChatMessageSent(const QString message);


private:
    // Core Methods
    void setupConnections();
    void resetGameState();
    void handleServerMessage(const QString message);

    // Card Selection Logic
    void processCardSelection(int index, const QString cardName);
    void performRandomCardSelection();
    void sendCardSelectionToServer(const QString cardName);

    // Timer Management
    void startCardSelectionTimer();// start 30 seconds timer to select the card
    void startWarningTimer();// start of the warning for 10 last seconds of select the card
    void startStopTimer();// stop timer after 30 seconds
    void stopAllTimers();

    // Game Control
    void handleStopRequest();
    void handleResumeRequest();
    void handleGameFinish();

    // Network Communication
    void sendToServer(const QString message);
    void sendNoSelectionWarning();// 8;username"
    void sendStopTimeoutWarning();// 9;username"

    // Game State Management
    void updateGameState(const QString state);
    void checkRandomSelectionLimit();// random selection for 2 times
    void checkStopUsageLimit();// stop usage for 2 times
    void disableStopButton();// stop button controller

    // manage chat
    void handleChatMessage(const QJsonObject message);
    void sendChatMessageToServer(const QString message);
    QString m_playerUsername;

    // Core Components
    GameUI* m_gameUI;
    SocketHandler* m_socketHandler;
    QString m_username;

    // Timers
    QTimer* m_cardSelectionTimer;// 30 seconds to select the card
    QTimer* m_warningTimer;//warning 10 seconds of select the card
    QTimer* m_stopTimer;//stop timer

    // Game Data
    QStringList m_currentRequestedCards;
    QStringList m_currentSelectedCards;
    QString m_gameState;// idle, playing, stopped, finished

    // Time Tracking
    int m_remainingCardTime;// reminded time(30s)
    int m_remainingWarningTime;// reminded time warning (10s)
    int m_remainingStopTime;// reminded time stop (30s)

    // Usage Counters
    int m_randomSelectionCount;//random selection (MAX = 2)
    int m_stopUsageCount;// use stop button stop (MAX = 2)

    // State Flags
    bool m_isGameActive;// active game
    bool m_isGamePaused;// pause game
    //bool m_isMyTurn;// is my choice
    bool m_inWarningMode;// is it the warning state
    bool m_stopButtonDisabled;// stop button state

    // Constants
    static const int TOTAL_CARD_TIME = 30;// 30 seconds max
    static const int WARNING_TIME = 10;// 10 seconds max - warning
    static const int STOP_TIME = 30;// 30 seconds - stop
    static const int MAX_RANDOM_SELECTIONS = 2;// at most 2 times for random choice
    static const int MAX_STOP_USAGE = 2;// at most 2 times for  stop


    // new functions
    void handleServerPause();
    void handleServerContinue();
    void saveCurrentTimerState();
    void restoreTimerState();

    QString m_savedTimerType;     // "card", "warning", "stop", "none"
    int m_savedRemainingTime;
    bool m_isServerPaused;

};

#endif // GAMEUICONTROLLER_H
