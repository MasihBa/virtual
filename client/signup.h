// #ifndef SIGNUP_H
// #define SIGNUP_H

// #include <QMainWindow>
// #include <QString>
// #include "sockethandler.h"

// QT_BEGIN_NAMESPACE
// namespace Ui { class SignUp; }
// QT_END_NAMESPACE

// class SignUp : public QMainWindow
// {
//     Q_OBJECT

// public:
//     explicit SignUp(SocketHandler* socketHandler, QWidget *parent = nullptr);
//     ~SignUp() override;

// private slots:
//     void onSignupClicked();
//     void onConnected();
//     void onMessageReceived(const QString& msg);
//     void onErrorOccurred(const QString& errorString);
//     void onDisconnected();

// private:
//     Ui::SignUp *ui;
//     SocketHandler *m_socketHandler;
//     QString pendingSignupMsg;
//     QString firstName;
//     QString lastName;
//     QString username;
//     QString password;
//     QString email;
//     QString phoneNumber;
//     bool checkValidFirstName();
//     bool checkValidLastName();
//     bool checkValidUsername();
//     bool checkValidEmail();
//     bool checkValidPassword();
//     bool checkValidPhoneNumber();
//     QString getUsername();
// signals:
//     void signupCompleted();

// };

// #endif // SIGNUP_H
#ifndef SIGNUP_H
#define SIGNUP_H

#include <QMainWindow>
#include <QString>
#include "sockethandler.h"
#include "user.h"


QT_BEGIN_NAMESPACE
namespace Ui { class SignUp; }
QT_END_NAMESPACE

class SignUp : public QMainWindow
{
    Q_OBJECT

public:
    explicit SignUp(SocketHandler* socketHandler, QWidget *parent = nullptr);
    ~SignUp() override;

signals:
    void signupCompleted();

public slots:
    void onSignupClicked();
    void onConnected();
    void onMessageReceived(const QString& msg);
    void onErrorOccurred(const QString& errorString);
    void onDisconnected();

private:
    Ui::SignUp *ui;
    SocketHandler *m_socketHandler;
    QString pendingSignupMsg;
    QString firstName;
    QString lastName;
    QString username;
    QString password;
    QString email;
    QString phoneNumber;
    User* signupUser;
    bool checkValidFirstName();
    bool checkValidLastName();
    bool checkValidUsername();
    bool checkValidEmail();
    bool checkValidPassword();
    bool checkValidPhoneNumber();
};

#endif // SIGNUP_H
