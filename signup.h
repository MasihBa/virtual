#ifndef SIGNUP_H
#define SIGNUP_H

#include <QPushButton>
#include <QString>
#include <QWidget>
#include<QMainWindow>
#include<Qlabel>
#include<QMessageBox>
namespace Ui {
class SignUp;
}

class SignUp : public QMainWindow
{
    Q_OBJECT

public:
    explicit SignUp(QWidget *parent = nullptr);
    ~SignUp();
    bool checkValidFirstName();
    bool checkValidLastName();
    bool checkValidUsername();
    bool checkValidEmail();
    bool checkValidPassword();
    bool checkValidPhoneNumber();

public slots:
    void onSignupClicked();

private:
    Ui::SignUp *ui;
    QString firstName;
    QString lastName;
    QString username;
    QString email;
    QString phoneNumber;
    QString password;
    QLabel* labelErrorMessage;
};

#endif // SIGNUP_H
