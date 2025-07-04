#include "signup.h"
#include "ui_signup.h"
#include <QRegularExpression>
#include <QMessageBox>
#include <QDebug>

SignUp::SignUp(SocketHandler* socketHandler, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SignUp)
    , m_socketHandler(socketHandler)
{
    ui->setupUi(this);

    connect(ui->signupPushButton, &QPushButton::clicked,this, &SignUp::onSignupClicked);
    disconnect(m_socketHandler, &SocketHandler::connected, nullptr, nullptr);
    connect(m_socketHandler, &SocketHandler::connected,this, &SignUp::onConnected);
    disconnect(m_socketHandler, &SocketHandler::messageReceived, nullptr, nullptr);
    connect(m_socketHandler, &SocketHandler::messageReceived,this, &SignUp::onMessageReceived);
    disconnect(m_socketHandler, &SocketHandler::errorOccurred, nullptr, nullptr);
    connect(m_socketHandler, &SocketHandler::errorOccurred,this, &SignUp::onErrorOccurred);
    disconnect(m_socketHandler, &SocketHandler::disconnected, nullptr, nullptr);
    connect(m_socketHandler, &SocketHandler::disconnected,this, &SignUp::onDisconnected);
}

SignUp::~SignUp()
{
    delete ui;
}

bool SignUp::checkValidFirstName() {
    return QRegularExpression("^[a-zA-Z]+$")
    .match(firstName).hasMatch();
}

bool SignUp::checkValidLastName() {
    return QRegularExpression("^[a-zA-Z]+$")
    .match(lastName).hasMatch();
}

bool SignUp::checkValidUsername() {
    return QRegularExpression("^[a-zA-Z0-9]{4,}$")
    .match(username).hasMatch();
}

bool SignUp::checkValidEmail() {
    return QRegularExpression("^[\\w.-]+@gmail\\.com$")
    .match(email).hasMatch();
}

bool SignUp::checkValidPassword() {
    return QRegularExpression("^[a-zA-Z0-9]{6,}$")
    .match(password).hasMatch();
}

bool SignUp::checkValidPhoneNumber() {
    return QRegularExpression("^98\\d{10}$")
    .match(phoneNumber).hasMatch();
}

void SignUp::onSignupClicked()
{
    firstName   = ui->firstnameLineEdit_2->text().trimmed();
    lastName    = ui->lastnameLineEdit_2->text().trimmed();
    username    = ui->usernameLineEdit_2->text().trimmed();
    password    = ui->passwordLineEdit_2->text().trimmed();
    email       = ui->emailLineEdit_2->text().trimmed();
    phoneNumber = ui->phonenumberLineEdit_2->text().trimmed();

    QString error;
    if (!checkValidFirstName()) error = "First name must contain only letters.";
    else if (!checkValidLastName()) error = "Last name must contain only letters.";
    else if (!checkValidUsername()) error = "Username must be alphanumeric (min 4 chars).";
    else if (!checkValidEmail()) error = "Email must end with @gmail.com.";
    else if (!checkValidPassword()) error = "Password must be at least 6 letters or digits.";
    else if (!checkValidPhoneNumber()) error = "Phone must be 12 digits starting with 98.";

    if (!error.isEmpty()) {
        QMessageBox::warning(this, "Signup Failed", error);
        return;
    }

    pendingSignupMsg = QString("1;%1;%2;%3;%4;%5;%6").arg(firstName). arg(lastName). arg(phoneNumber). arg(email). arg(username). arg(password);
    m_socketHandler->sendMessage(pendingSignupMsg);
}

void SignUp::onConnected()
{
    if (!pendingSignupMsg.isEmpty()) {
        m_socketHandler->sendMessage(pendingSignupMsg);
        pendingSignupMsg.clear();
    }
}

void SignUp::onMessageReceived(const QString& msg)
{
    qDebug() << "Server reply:" << msg;
    if (msg == "1") {
        currentUser.firstName = firstName;
        currentUser.lastName = lastName;
        currentUser.email = email;
        currentUser.phoneNumber = phoneNumber;
        currentUser.username = username;
        currentUser.password = password;
        QMessageBox::information(this, "Signup", "Signup successful! Now sign in.");
        emit signupCompleted();
        this->close();
    }

    else {
    QMessageBox::warning(this, "Signup Failed", msg);
    }
}

void SignUp::onErrorOccurred(const QString& errorString)
{
    qDebug() << "Socket error:" << errorString;
    QMessageBox::warning(this, "Network Error", errorString);
}

void SignUp::onDisconnected()
{
    qDebug() << "Disconnected from server";
}

