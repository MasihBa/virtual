// signup.cpp
#include "signup.h"
#include <QRegularExpression>
//#include "ui_signup.h"

SignUp::SignUp(QWidget *parent)
    : QWidget(parent)
    , ui1(new Ui::SignUp)
{
    ui1->setupUi(this);
    connect(ui1->signupPushButton, &QPushButton::clicked, this, &SignUp::onSignupClicked);
}

SignUp::~SignUp()
{
    delete ui1;
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
    firstName = ui1->firstnameLineEdit->text();
    lastName = ui1->lastnameLineEdit->text();
    username = ui1->usernameLineEdit->text();
    password = ui1->passwordLineEdit->text();
    email = ui1->emailLineEdit->text();
    phoneNumber = ui1->phonenumberLineEdit->text();

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
        ui1->labelErrorMessage->setStyleSheet("color: red;");
        ui1->labelErrorMessage->setText(error);
    } else {
        ui1->labelErrorMessage->setStyleSheet("color: green;");
        ui1->labelErrorMessage->setText("Signup successful!");
    }
}
