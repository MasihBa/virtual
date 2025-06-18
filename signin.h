#ifndef SIGNIN_H
#define SIGNIN_H
#include<QString>
#include<QMainWindow>
#include <QWidget>


namespace Ui{ class SignIn;}
QT_END_NAMESPACE
class SignIn: QMainWindow{
private:
    QString enteredPass;
    QString enteredUsername;
    Ui::SignIn *ui;
public:
    explicit SignIn(const QString& enteredPassByUser,const QString& enteredUsernameByUser, QWidget* parent);
    bool validatePassword();
    bool validateUsername();
    ~SignIn();
private slots:
    void onSignInClicked();

};

#endif // SIGNIN_H
