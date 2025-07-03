// FINDPASSWORD_H
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

public slots:
    void onPasswordRecoveryClicked();
    void onMessageReceived(const QString& msg);
    void onErrorOccurred(const QString& errorString);

private:
    bool checkValidUsername(const QString& username);
    bool checkValidPhoneNumber(const QString& phoneNumber);
    bool checkValidPassword(const QString& password);
    void sendPasswordChangeRequest();

    Ui::FindPassword *ui;
    SocketHandler   *m_socketHandler;
    bool m_isVerificationStep;
    QString m_verifiedUsername;
    QString m_verifiedPhone;
};

#endif // FINDPASSWORD_H
