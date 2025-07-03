#include "signin.h"
#include "ui_signin.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QDebug>
#include <QTcpSocket>

SignIn::SignIn(SocketHandler* socketHandler, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SignIn)
    , m_socketHandler(socketHandler)
{
    ui->setupUi(this);

    connect(ui->signInpushButton_signInPage, &QPushButton::clicked,
            this, &SignIn::onSignInClicked);
    connect(ui->signupsigninpushButton, &QPushButton::clicked,
            this, &SignIn::onSignupButtonClicked);
    connect(ui->passwordrecoverysigninpushButton, &QPushButton::clicked,
            this, &SignIn::onPasswordRecoveryButtonClicked);

    if (m_socketHandler) {
        disconnect(m_socketHandler, &SocketHandler::messageReceived, nullptr, nullptr);
        connect(m_socketHandler, &SocketHandler::messageReceived,
                this, &SignIn::onMessageReceived);
        disconnect(m_socketHandler, &SocketHandler::connected, nullptr, nullptr);
        connect(m_socketHandler, &SocketHandler::connected,
                this, &SignIn::onConnected);
        disconnect(m_socketHandler, &SocketHandler::errorOccurred, nullptr, nullptr);
        connect(m_socketHandler, &SocketHandler::errorOccurred,
                this, &SignIn::onErrorOccurred);
    }
}

SignIn::~SignIn() {
    delete ui;
}

bool SignIn::checkValidUsername(const QString &username) {
    return QRegularExpression("^[a-zA-Z0-9]{4,}$")
    .match(username).hasMatch();
}

bool SignIn::checkValidPassword(const QString &password) {
    return QRegularExpression("^[a-zA-Z0-9]{6,}$")
    .match(password).hasMatch();
}

void SignIn::onSignInClicked() {
    QString user = ui->usernameInSignInPagelineEdit->text().trimmed();
    QString pass = ui->passInSignInPagelineEdit->text().trimmed();

    if (user.isEmpty() || pass.isEmpty()) {
        QMessageBox::warning(this, "SignIn Error",
                             "Please enter username and password");
        return;
    }
    if (!checkValidUsername(user)) {
        QMessageBox::warning(this, "Invalid Username",
                             "Username must be at least 4 letters/numbers");
        return;
    }
    if (!checkValidPassword(pass)) {
        QMessageBox::warning(this, "Invalid Password",
                             "Password must be at least 6 letters/numbers");
        return;
    }

    QString msg = QString("2;%1;%2").arg(user, pass);
    qDebug() << "SignIn msg:" << msg;

    if (m_socketHandler->state() == QTcpSocket::ConnectedState) {
        m_socketHandler->sendMessage(msg);
        pendingSigninMsg.clear();
    } else {
        pendingSigninMsg = msg;
    }
}

void SignIn::onMessageReceived(const QString &msg) {
    qDebug() << "Server reply:" << msg;
    if (msg == "1") {
        QString _username = ui->usernameInSignInPagelineEdit->text().trimmed();
        QMessageBox::information(this, "SignIn", "Login successful");
        emit signInSuccess(_username);
        this->close();
    } else if(msg == "0"){
        QMessageBox::warning(this, "Failed", "Invalid username or password.");
    }
    else{
        // QMessageBox::warning(this, "SignIn Failed", msg);
        QMessageBox::warning(this, "SignIn Failed", "your enter the wrong password or username.");
    }
}

void SignIn::onConnected() {
    if (!pendingSigninMsg.isEmpty()) {
        m_socketHandler->sendMessage(pendingSigninMsg);
        pendingSigninMsg.clear();
    }
}

void SignIn::onErrorOccurred(const QString &err) {
    QMessageBox::critical(this, "Socket Error", err);
}

void SignIn::onSignupButtonClicked() {
    emit requestSignUpPage();
}

void SignIn::onPasswordRecoveryButtonClicked() {
    emit requestPasswordRecoveryPage();
}

void SignIn::clearLoginFields()
{
    ui->usernameInSignInPagelineEdit->clear();
    ui->passInSignInPagelineEdit->clear();
}
