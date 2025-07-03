// #ifndef MENU_H
// #define MENU_H

// #include <QPushButton>
// #include <QWidget>
// #include "signup.h"
// #include <history.h>
// #include<changeInfo.h>
// // _ startGame _ ((logOut)??)



// namespace Ui { class Menu; }


// class Menu : public QWidget
// {
//     Q_OBJECT

// public:
//     explicit Menu(SocketHandler* socketHandler, QWidget *parent = nullptr);
//     ~Menu();

// private slots:
//     void handleStartGame();
//     void handleHistory();
//     void handleChangeInfo();
//     void handleLogOut();

// private:
//     Ui::Menu *ui;
//     SignUp *signUpPage;
//     SocketHandler* m_socketHandler;
//     // History *historyPage;
//     // StartGame *startGamePage;
//     // ChangeUserData *changeUserDataPage;
// };

// #endif // MENU_H


#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include "signup.h"
#include "history.h"
#include <QPushButton>
#include "changeInfo.h"
#include "sockethandler.h"
#include<waiting.h>
#include <QApplication>

namespace Ui { class Menu; }

class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(SocketHandler* socketHandler, const QString &_username, QWidget *parent = nullptr);
    ~Menu();

signals:
    void logOutRequested();
    void gameStartRequested();
    // void onStartGameClicked();


public slots:
    void handleStartGame();
    void handleHistory();
    void handleChangeInfo();
    void handleLogOut();
    void onInfoChanged();
    void onInfoCancelled();
    void onHistoryDataReceived(const QString &data);
    void onHistoryClosed();
    void onGameStarted(const QString &gameData);
    void onWaitingCancelled();
    void onStartGameClicked();

private:
    Ui::Menu *ui;
    SignUp *signUpPage;
    SocketHandler* m_socketHandler;
    ChangeInfo* changeInfoPage;
    QString m_username;
    History *historyPage;
    Waiting *waitingPage;

};

#endif // MENU_H
