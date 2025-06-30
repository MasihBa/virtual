// #ifndef GAMEUICONTROLLER_H
// #define GAMEUICONTROLLER_H

// #include <QObject>
// #include <QTimer>
// #include <QJsonObject>
// #include <QJsonDocument>
// #include <QStringList>
// #include <QRandomGenerator>
// #include <QDebug>
// #include "gameui.h"
// #include "sockethandler.h"

// class GameUIController
// {
//     Q_OBJECT

// public:

//     explicit GameUIController(GameUI* gameUI, SocketHandler* socketHandler, QObject *parent = nullptr);
//     ~GameUIController();
//     void startNewGame();
//     void stopGame();
//     void resumeGame();
//     void exitGame();
// signals:
//     void gameFinished();
//     void returnToMenu();
//     void gameError(const QString& error);

// private slots:
//     //
//     void onCardSelected(int index, const QString& cardName);
//     void onSelectedCardClicked(int index);
//     void onStopRequested();
//     void onResumeRequested();
//     void onExitRequested();
//     // for connecting to server
//     void onServerMessageReceived(const QString& message);
//     // for handling the time during the game
//     void onGameTimerTick();
//     void onWarningTimerTick();
//     void onStopTimerTick();
// private:
//     void setupConnections();
//     void resetGameState();
//     void handleServerMessage(const QJsonObject& message);
//     // select cards:
//     void processCardSelection(int index, const QString& cardName);
//     void performRandomCardSelection();
//     void sendCardSelectionToServer(const QString& cardName);

//     // manage time:
//     void startCardSelectionTimer();
//     void startWarningTimer();
//     void startStopTimer();
//     void stopAllTimers();

//     // stop/ resume the game:
//     void handleStopRequest();
//     void handleResumeRequest();
//     void handleStopFromServer();
//     void handleResumeFromServer();

//     // manage the time:
//     void handleCardTimeout();
//     void handleStopTimeoutExpired();
//     void checkRandomSelectionLimit();
//     void checkStopUsageLimit();

//     // // :
//     // void sendToServer(const QString& action, const QJsonObject& data = QJsonObject());
//     // void sendStopRequest();
//     // void sendResumeRequest();
//     // void sendRandomSelectionNotification();
//     // void sendStopTimeoutNotification();
//     // void sendExitRequest();

//     // game state:
//     void updateGameState(const QString& state);
//     void handleGameEnd(const QString& reason);
//     void returnAllPlayersToMenu(const QString& reason);

// private:
//     // connecting to ui of the game(gameUI) and use m_socketHandler to connect to server:
//     GameUI* m_gameUI;
//     SocketHandler* m_socketHandler;

//     // timers:
//     QTimer* m_gameTimer;
//     QTimer* m_warningTimer;
//     QTimer* m_stopTimer;
//     // game states:
//     QStringList m_currentRequestedCards;
//     QStringList m_currentSelectedCards;
//     QString m_currentPlayer;
//     QString m_gameState;// "playing", "stopped", "warning", "finished"

//     // variables for the timers:
//     int m_cardSelectionTime;//20 seconds
//     int m_warningTimeLeft;//10 seconds
//     int m_stopTimeLeft;//30 seconds
//     int m_remainingCardTime;
//     int m_remainingWarningTime;
//     int m_remainingStopTime;
//     // i should insert a variable for the timer of the "user exit"(60 s)
//     // the count of the random choose
//     int m_randomSelectCount;
//     //the cuount of the stop the game
//     int m_stopCount;//

//     // all of the flags(I should add an flag for exit user)
//     bool m_isGameActive;
//     bool m_isPuased;
//     // bool m_waitingForCards;
//     // bool m_inWarningMode;
//     bool m_isMyTurn;

//     // all of defines
//     static const int MAX_RANDOM_SELECTIONS = 2;
//     static const int MAX_STOPS= 2;
//     static const int CARD_SELECTION_TIME = 20;
//     static const int WARNING_TIME = 10;
//     static const int STOP_TIME = 30;
//     QString m_playerId;// the username of the player


// };

// #endif // GAMEUICONTROLLER_H
// gameUIController.h
// #ifndef GAMEUICONTROLLER_H
// #define GAMEUICONTROLLER_H

// #include <QObject>
// #include <QTimer>
// #include <QStringList>
// #include <QJsonObject>
// #include <QRandomGenerator>
// #include "gameui.h"
// #include "sockethandler.h"

// // Constants
// const int CARD_SELECTION_TIME = 20; // seconds
// const int WARNING_TIME = 10;        // seconds
// const int STOP_TIME = 30;          // seconds
// const int MAX_RANDOM_SELECTIONS = 2;
// const int MAX_STOPS = 2;
// const int MAX_STOP_USAGE = 2;

// class GameUIController : public QObject
// {
//     Q_OBJECT

// public:
//     explicit GameUIController(GameUI* gameUI, SocketHandler* socketHandler, QObject *parent = nullptr);
//     ~GameUIController();

//     // Public methods
//     void startGame();
//     void stopGame();
//     void pauseGame();
//     void resumeGame();

// public slots:
//     // UI Event Handlers
//     void onCardSelected(int cardIndex, const QString& cardValue);
//     void onSelectedCardClicked(int index);
//     void onSwapRequested(int targetPlayer);
//     void onStopRequested();
//     void onResumeRequested();
//     void onExitRequested();

//     // Server Message Handler
//     void onMessageReceived(const QString& message);

// private slots:
//     // Timer Event Handlers
//     void onGameTimerTick();
//     void onWarningTimerTick();
//     void onStopTimerTick();

//     // Timeout Handlers
//     void onCardSelectionTimeout();
//     void onWarningTimeout();
//     void onStopTimeout();

// signals:
//     void gameEnded();
//     void returnToMenu();
//     void gameFinished();

// private:
//     // Core components
//     GameUI* m_gameUI;
//     SocketHandler* m_socketHandler;

//     // Timers
//     QTimer* m_gameTimer;
//     QTimer* m_warningTimer;
//     QTimer* m_stopTimer;

//     // Game state variables
//     bool m_isGameActive;
//     bool m_isMyTurn;
//     bool m_isPaused;
//     bool m_gameActive;
//     bool m_gameStopped;
//     bool m_waitingForCards;
//     bool m_inWarningMode;

//     // Time variables
//     int m_cardSelectionTime;
//     int m_warningTimeLeft;
//     int m_stopTimeLeft;
//     int m_warningTime;
//     int m_stopTime;
//     int m_remainingCardTime;
//     int m_remainingWarningTime;
//     int m_remainingStopTime;

//     // Counters
//     int m_randomSelectionCount;
//     int m_stopUsageCount;

//     // Game data
//     QString m_playerId;
//     QString m_currentPlayer;
//     QString m_gameState;
//     QStringList m_currentRequestedCards;
//     QStringList m_currentSelectedCards;

//     // Private methods
//     void setupConnections();
//     void resetGameState();
//     void startCardSelectionTimer();
//     void startWarningTimer();
//     void startStopTimer();
//     void stopAllTimers();
//     void selectRandomCard();
//     void handleServerMessage(const QJsonObject& jsonMessage);
//     void updateGameState(const QJsonObject& gameState);
//     void updateDisplayedCards(const QStringList& requestedCards, const QStringList& selectedCards);
// };

// #endif // GAMEUICONTROLLER_H
// gameUIController.h
// #ifndef GAMEUICONTROLLER_H
// #define GAMEUICONTROLLER_H

// #include <QObject>
// #include <QTimer>
// #include <QStringList>
// #include <QJsonObject>
// #include <QJsonDocument>
// #include <QRandomGenerator>
// #include <QMetaObject>
// #include "gameui.h"
// #include "sockethandler.h"

// // Constants
// const int CARD_SELECTION_TIME = 20; // seconds
// const int WARNING_TIME = 10;        // seconds
// const int STOP_TIME = 30;          // seconds
// const int MAX_RANDOM_SELECTIONS = 2;
// const int MAX_STOPS = 2;
// const int MAX_STOP_USAGE = 2;

// class GameUIController : public QObject
// {
//     Q_OBJECT

// public:
//     explicit GameUIController(GameUI* gameUI, SocketHandler* socketHandler, QObject *parent = nullptr);
//     ~GameUIController();

//     // Public methods
//     void startNewGame();
//     void stopGame();
//     void resumeGame();
//     void exitGame();

// public slots:
//     // UI Event Handlers
//     void onCardSelected(int cardIndex, const QString& cardValue);
//     void onSelectedCardClicked(int index);
//     void onSwapRequested(int targetPlayer);
//     void onStopRequested();
//     void onResumeRequested();
//     void onExitRequested();

//     // Server Message Handler
//     void onMessageReceived(const QString& message);

// private slots:
//     // Timer Event Handlers
//     void onGameTimerTick();
//     void onWarningTimerTick();
//     void onStopTimerTick();

//     // Timeout Handlers
//     void onCardSelectionTimeout();
//     void onWarningTimeout();
//     void onStopTimeout();

// signals:
//     void gameEnded();
//     void returnToMenu();
//     void gameFinished();

// private:
//     // Core components
//     GameUI* m_gameUI;
//     SocketHandler* m_socketHandler;

//     // Timers
//     QTimer* m_gameTimer;
//     QTimer* m_warningTimer;
//     QTimer* m_stopTimer;

//     // Game state variables
//     bool m_isGameActive;
//     bool m_isMyTurn;
//     bool m_isPaused;
//     bool m_gameActive;
//     bool m_gameStopped;
//     bool m_waitingForCards;
//     bool m_inWarningMode;

//     // Time variables
//     int m_cardSelectionTime;
//     int m_warningTimeLeft;
//     int m_stopTimeLeft;
//     int m_warningTime;
//     int m_stopTime;
//     int m_remainingCardTime;
//     int m_remainingWarningTime;
//     int m_remainingStopTime;

//     // Counters
//     int m_randomSelectionCount;
//     int m_stopUsageCount;

//     // Game data
//     QString m_playerId;
//     QString m_currentPlayer;
//     QString m_gameState;
//     QStringList m_currentRequestedCards;
//     QStringList m_currentSelectedCards;

//     void setupConnections();
//     void resetGameState();
//     void updateDisplayedCards(const QStringList& requestedCards, const QStringList& selectedCards);
//     void processCardSelection(int cardIndex, const QString& cardValue);
//     void performRandomCardSelection();
//     void selectRandomCard();

//     // Timer management
//     void startCardSelectionTimer();
//     void startWarningTimer();
//     void startStopTimer();
//     void stopAllTimers();

//
//     void sendToServer(const QString& message);
//     void sendToServer(const QString& action, const QJsonObject& data);
//     void sendCardSelectionToServer(const QString& cardValue);
//     void sendStopRequest();
//     void sendResumeRequest();
//     void sendRandomSelectionNotification();
//     void sendStopTimeoutNotification();
//     void sendExitRequest();

//     // Message handling
//     void handleServerMessage(const QJsonObject& jsonMessage);
//     void updateGameState(const QJsonObject& gameState);

//     // Game logic helpers
//     bool canUseRandomSelection() const;
//     bool canUseStop() const;
//     void handleStopRequest();
//     void handleResumeRequest();
// };

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
    explicit GameUIController(GameUI* gameUI, SocketHandler* socketHandler, QObject *parent = nullptr);
    ~GameUIController();
    void startNewGame();
    void stopGame();
    void resumeGame();
    void exitGame();

signals:
    void gameFinished();
    void returnToMenu();
    void gameError(const QString& error);

private slots:
    void onCardSelected(int index, const QString& cardName);
    void onSelectedCardClicked(int index);
    void onStopRequested();
    void onResumeRequested();
    void onExitRequested();
    void onServerMessageReceived(const QString& message);
    void onGameTimerTick();
    void onWarningTimerTick();
    void onStopTimerTick();

    //NEW
    void onCardSelectionTimeout();
    void onWarningTimeout();
    void onStopTimeout();

private:
    void setupConnections();
    void resetGameState();
    void handleServerMessage(const QJsonObject& message);
    void processCardSelection(int index, const QString& cardName);
    void performRandomCardSelection();
    void sendCardSelectionToServer(const QString& cardName);
    void startCardSelectionTimer();
    void startWarningTimer();
    void startStopTimer();
    void stopAllTimers();
    void handleStopRequest();
    void handleResumeRequest();
    void handleStopFromServer();
    void handleResumeFromServer();
    void handleCardTimeout();
    void handleStopTimeoutExpired();
    void checkRandomSelectionLimit();
    void checkStopUsageLimit();
    void updateGameState(const QString& state);
    void handleGameEnd(const QString& reason);
    void returnAllPlayersToMenu(const QString& reason);

    //NEW
    void sendToServer(const QString& action, const QJsonObject& data);
    void sendToServer(const QString& action);

    void sendStopRequest();
    void sendResumeRequest();
    void sendRandomSelectionNotification();
    void sendStopTimeoutNotification();
    void sendExitRequest();
    void updateDisplayedCards(const QStringList& requestedCards, const QStringList& selectedCards);


// private:
    GameUI* m_gameUI;
    SocketHandler* m_socketHandler;

    QTimer* m_gameTimer;
    QTimer* m_warningTimer;
    QTimer* m_stopTimer;

    QStringList m_currentRequestedCards;
    QStringList m_currentSelectedCards;
    QString m_currentPlayer;
    QString m_gameState;

    int m_cardSelectionTime;
    int m_warningTimeLeft;
    int m_stopTimeLeft;
    int m_remainingCardTime;
    int m_remainingWarningTime;
    int m_remainingStopTime;
    int m_randomSelectCount;
    int m_stopCount;
    int m_stopTime;

    bool m_isGameActive;
    bool m_isPuased;
    bool m_isMyTurn;
    bool m_waitingForCards;
    bool m_inWarningMode;
    int m_warningTime;
    QString m_playerId;

    static const int MAX_RANDOM_SELECTIONS = 2;
    static const int MAX_STOP_USAGE = 2;
    static const int CARD_SELECTION_TIME = 20;
    static const int WARNING_TIME = 10;
    static const int STOP_TIME = 30;
};

#endif // GAMEUICONTROLLER_H
