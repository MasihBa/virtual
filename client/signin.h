// #ifndef SIGNIN_H
// #define SIGNIN_H

// #include <QMainWindow>
// #include "sockethandler.h"
// #include "signup.h"

// namespace Ui {
// class SignIn;
// }

// class SignIn : public QMainWindow
// {
//     Q_OBJECT

// signals:
//     void requestPasswordRecoveryPage();
//     void signInSuccess();

// public:
//     explicit SignIn(SocketHandler* socketHandler, const QString& enteredPassByUser = QString(), const QString& enteredUsernameByUser = QString(), QWidget *parent = nullptr);
//     ~SignIn() override;

// private slots:
//     void onSignInClicked();
//     void onMessageReceived(const QString& msg);
//     void onConnected();
//     void onErrorOccurred(const QString& errorString);
//     void onSignupButtonClicked();
//     void onPasswordRecoveryButtonClicked();

// private:
//     Ui::SignIn *ui;
//     SocketHandler *m_socketHandler;
//     QString pendingSigninMsg;
//     QString enteredUsername;
//     QString enteredPass;
//     SignUp* signUpPage = nullptr;

//     bool checkValidUsername(const QString &username);
//     bool checkValidPassword(const QString &password);
// };

// #endif // SIGNIN_H
#ifndef SIGNIN_H
#define SIGNIN_H

#include <QMainWindow>
#include "sockethandler.h"

namespace Ui {
class SignIn;
}

class SignIn : public QMainWindow
{
    Q_OBJECT

signals:
    void requestSignUpPage();
    void requestPasswordRecoveryPage();
    void signInSuccess(const QString& _username);

public:
    explicit SignIn(SocketHandler* socketHandler, QWidget *parent = nullptr);
    ~SignIn() override;

public slots:
    void onSignInClicked();
    void onMessageReceived(const QString& msg);
    void onConnected();
    void onErrorOccurred(const QString& errorString);
    void onSignupButtonClicked();
    void onPasswordRecoveryButtonClicked();
    void clearLoginFields();

private:
    Ui::SignIn *ui;
    SocketHandler *m_socketHandler;
    QString pendingSigninMsg;

    bool checkValidUsername(const QString &username);
    bool checkValidPassword(const QString &password);
};

#endif // SIGNIN_H
