#ifndef SIGNUP_H
#define SIGNUP_H

#include <QString>
#include <QWidget>
namespace Ui {
class SignUp;
}

class SignUp : public QWidget
{
    Q_OBJECT

public:
    explicit SignUp(QWidget *parent = nullptr);
    ~SignUp();
    bool checkValidFirstName() ;
    bool checkValidLastName() ;
    bool checkValidUsername() ;
    bool checkValidEmail() ;
    bool checkValidPassword() ;
    bool checkValidPhoneNumber() ;

public slots:
    void onSignupClicked();

private:
    Ui::SignUp *ui1;
    QString firstName;
    QString lastName;
    QString username;
    QString email;
    QString phoneNumber;
    QString password;
};

#endif // SIGNUP_H
