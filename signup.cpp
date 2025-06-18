// signup.cpp
#include "ui_signup.h"
#include "signup.h"
#include <QRegularExpression>

SignUp::SignUp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SignUp)
{
    ui->setupUi(this);
    connect(ui->signupPushButton, &QPushButton::clicked, this, &SignUp::onSignupClicked);
}

SignUp::~SignUp()
{
    delete ui;
}

bool SignUp::checkValidFirstName()
{
    return QRegularExpression("^[a-zA-Z]+$").match(firstName).hasMatch();
}

bool SignUp::checkValidLastName()
{
    return QRegularExpression("^[a-zA-Z]+$").match(lastName).hasMatch();
}

bool SignUp::checkValidUsername()
{
    return QRegularExpression("^[a-zA-Z0-9]{4,}$").match(username).hasMatch();
}

bool SignUp::checkValidEmail()
{
    return QRegularExpression("^[\\w.-]+@gmail\\.com$").match(email).hasMatch();
}

bool SignUp::checkValidPassword()
{
    return QRegularExpression("^[a-zA-Z0-9]{6,}$").match(password).hasMatch();
}

bool SignUp::checkValidPhoneNumber()
{
    return QRegularExpression("^98\\d{10}$").match(phoneNumber).hasMatch();
}

void SignUp::onSignupClicked()
{
    firstName = ui->firstnameLineEdit_2->text();
    lastName = ui->lastnameLineEdit_2->text();
    username = ui->usernameLineEdit_2->text();
    password = ui->passwordLineEdit_2->text();
    email = ui->emailLineEdit_2->text();
    phoneNumber = ui->phonenumberLineEdit_2->text();

    QString error;
    if (!checkValidFirstName()) {
        error = "First name must contain only letters.";
    } else if (!checkValidLastName()) {
        error = "Last name must contain only letters.";
    } else if (!checkValidUsername()) {
        error = "Username must be alphanumeric (min 4 chars).";
    } else if (!checkValidEmail()) {
        error = "Email must end with @gmail.com.";
    } else if (!checkValidPassword()) {
        error = "Password must be at least 6 letters or digits.";
    } else if (!checkValidPhoneNumber()) {
        error = "Phone must be 12 digits starting with 98.";
    }

    if (!error.isEmpty()) {
        QMessageBox::warning(this, "Signup Failed", error);  // پیام خطا
    } else {
        QMessageBox::information(this, "Signup Success", "Signup successful!");  // پیام موفقیت
    }
}
