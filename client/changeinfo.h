// changeinfo.h
#ifndef CHANGEINFOPAGE_H
#define CHANGEINFOPAGE_H

#include <QMainWindow>
#include "sockethandler.h"
#include<signup.h>
#include<QWidget>
#include<QString>
#include<user.h>
#include<QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class ChangeInfo; }
QT_END_NAMESPACE

class ChangeInfo : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChangeInfo(SocketHandler* socketHandler, const QString &username, QWidget* parent = nullptr);
    ~ChangeInfo() override;

signals:
    void infoChanged();
    void changeCancelled();

private slots:
    void onSaveClicked();
    void onCancelClicked();
    void onMessageReceived(const QString& msg);
    void onErrorOccurred(const QString& err);

private:
    Ui::ChangeInfo *ui;
    SocketHandler *m_socketHandler;
    QString c_username;
    QString firstName, lastName, email, phoneNumber, password;
    // void loadCurrentUserInfo();
    // bool validateInputs();
    // bool checkValidFirstName(const QString& fn);
    // bool checkValidLastName(const QString& ln);
    // bool checkValidEmail(const QString& em);
    // bool checkValidPhone(const QString& ph);
    // bool checkValidUsername(const QString& us);
    // bool checkValidPassword(const QString& pa);
    void requestUserInfo();
    void loadUserInfoToUI();
    bool validateInputs();
    bool checkValidFirstName(const QString& fn);
    bool checkValidLastName(const QString& ln);
    bool checkValidEmail(const QString& em);
    bool checkValidPhone(const QString& ph);
    bool checkValidUsername(const QString& us);
    bool checkValidPassword(const QString& pa);
};

#endif // CHANGEINFOPAGE_H
