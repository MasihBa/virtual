#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sockethandler.h"
#include "signin.h"
#include "signup.h"
#include "findpassword.h"
#include "menu.h"
#include "waiting.h"
#include "gameui.h"
#include "gameuicontroller.h"

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void onConnectClicked();
    void onConnected();
    void showSignInPage();
    void showSignUpPage();
    void showFindPasswordPage();
    void showMenuPage(const QString& _ysername);
    void onLogOutRequested();
    void onGameStartRequested();
    void onReturnToMenuFromGame();
    void onGameError(const QString& error);

    //void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    SocketHandler *m_socketHandler = nullptr;
    QString currentUsername;
    SignIn *signInPage = nullptr;
    SignUp *signUpPage = nullptr;
    FindPassword *findPasswordPage = nullptr;
    Menu *menuPage = nullptr;
    GameUI* gameUI = nullptr;
    GameUIController* gameUIController = nullptr;
};

#endif // MAINWINDOW_H



