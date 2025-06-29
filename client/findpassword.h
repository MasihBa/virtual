// // findpassword.h
// #ifndef FINDPASSWORD_H
// #define FINDPASSWORD_H

// #include<QWidget>
// #include<QMainWindow>
// #include "sockethandler.h"

// namespace Ui {
// class FindPassword;
// }

// class FindPassword : public QMainWindow

// {
//     Q_OBJECT
// public:
//     explicit FindPassword(SocketHandler* socketHandler, QMainWindow *parent = nullptr);
//     ~FindPassword() override;

// signals:
//     void backToSignIn();

// private slots:
//     void onPasswordRecoveryClicked();
//     void onMessageReceived(const QString& msg);

// private:
//     bool checkValidUsername(const QString& username);
//     bool checkValidPhoneNumber(const QString& phoneNumber);

//     Ui::FindPassword *ui;
//     SocketHandler   *m_socketHandler;
// };

// #endif // FINDPASSWORD_H
// findpassword.h
#ifndef FINDPASSWORD_H
#define FINDPASSWORD_H

#include <QMainWindow>
#include "sockethandler.h"

namespace Ui { class FindPassword; }

class FindPassword : public QMainWindow
{
    Q_OBJECT
public:
    explicit FindPassword(SocketHandler* socketHandler, QWidget *parent = nullptr);
    ~FindPassword() override;

signals:
    void recoveryCompleted();
    void backToSignIn();

private slots:
    void onPasswordRecoveryClicked();
    void onMessageReceived(const QString& msg);
    void onErrorOccurred(const QString& errorString);

private:
    bool checkValidUsername(const QString& username);
    bool checkValidPhoneNumber(const QString& phoneNumber);

    Ui::FindPassword *ui;
    SocketHandler   *m_socketHandler;
};

#endif // FINDPASSWORD_H

