// #include "signin.h"
// #include "ui_signin.h"
// #include <QMessageBox>
// #include <QRegularExpression>
// #include <QDebug>
// #include <QTcpSocket>

// SignIn::SignIn(SocketHandler* socketHandler, const QString& enteredPassByUser, const QString& enteredUsernameByUser, QWidget *parent)
//     : QMainWindow(parent)
//     , ui(new Ui::SignIn)
//     , m_socketHandler(socketHandler)
//     , pendingSigninMsg()
//     , enteredUsername(enteredUsernameByUser)
//     , enteredPass(enteredPassByUser)
//     , signUpPage(nullptr)
// {
//     ui->setupUi(this);

//     connect(ui->signInpushButton_signInPage, &QPushButton::clicked,
//             this, &SignIn::onSignInClicked);

//     connect(ui->signupsigninpushButton, &QPushButton::clicked,
//             this, &SignIn::onSignupButtonClicked);

//     connect(ui->passwordrecoverysigninpushButton, &QPushButton::clicked,
//             this, &SignIn::onPasswordRecoveryButtonClicked);

//     if (m_socketHandler) {
//         connect(m_socketHandler, &SocketHandler::messageReceived,
//                 this, &SignIn::onMessageReceived);
//         connect(m_socketHandler, &SocketHandler::connected,
//                 this, &SignIn::onConnected);
//         connect(m_socketHandler, &SocketHandler::errorOccurred,
//                 this, &SignIn::onErrorOccurred);
//     } else {
//         qDebug() << "Warning: SocketHandler is null in SignIn constructor!";
//     }
// }

// SignIn::~SignIn() {
//     delete ui;
// }

// bool SignIn::checkValidUsername(const QString &username)
// {
//     return QRegularExpression("^[a-zA-Z0-9]{4,}$").match(username).hasMatch();
// }

// bool SignIn::checkValidPassword(const QString &password)
// {
//     return QRegularExpression("^[a-zA-Z0-9]{6,}$").match(password).hasMatch();
// }

// void SignIn::onSignInClicked()
// {
//     QString username_input = ui->usernameInSignInPagelineEdit->text().trimmed();
//     QString password_input = ui->passInSignInPagelineEdit->text().trimmed();

//     if (username_input.isEmpty() || password_input.isEmpty()) {
//         QMessageBox::warning(this, "SignIn Error", "Please enter username and password");
//         return;
//     }

//     if (!checkValidUsername(username_input)) {
//         QMessageBox::warning(this, "Invalid Username", "Username must be at least 4 characters (letters/numbers only)");
//         return;
//     }
//     if (!checkValidPassword(password_input)) {
//         QMessageBox::warning(this, "Invalid Password", "Password must be at least 6 characters (letters/numbers only)");
//         return;
//     }

//     QString signinMsg = "2," + username_input + "," + password_input;
//     qDebug() << "Attempting SignIn with message:" << signinMsg;

//     if (m_socketHandler) {
//         if (m_socketHandler->state() == QTcpSocket::ConnectedState) {
//             m_socketHandler->sendMessage(signinMsg);
//             pendingSigninMsg.clear();
//         } else {
//             QMessageBox::critical(this, "Connection Error", "Not connected to server. Cannot sign in.");
//             pendingSigninMsg = signinMsg;
//         }
//     } else {
//         QMessageBox::critical(this, "Socket Error", "Socket handler is not available.");
//     }
// }

// void SignIn::onMessageReceived(const QString &msg)
// {
//     qDebug() << "Server response for SignIn:" << msg;

//     if (msg == "LoginSuccess") {
//         QMessageBox::information(this, "Successful SignIn", "Login was successful");
//         emit signInSuccess();
//     } else if (msg == "LoginFailed") {
//         QMessageBox::warning(this, "SignIn Failed", "Signin failed. Please check your credentials.");
//     }
// }

// void SignIn::onConnected()
// {
//     if (!pendingSigninMsg.isEmpty()) {
//         m_socketHandler->sendMessage(pendingSigninMsg);
//         pendingSigninMsg.clear();
//     }
// }

// void SignIn::onErrorOccurred(const QString &errorString)
// {
//     QMessageBox::critical(this, "Socket Error", "Error during communication: " + errorString);
// }

// void SignIn::onSignupButtonClicked()
// {
//     qDebug() << "Signup button clicked";

//     if (!signUpPage) {
//         signUpPage = new SignUp(m_socketHandler);
//         connect(signUpPage, &QObject::destroyed, [this]() {
//             this->show();
//             signUpPage = nullptr;
//         });
//     }

//     this->hide();
//     signUpPage->show();
// }

// void SignIn::onPasswordRecoveryButtonClicked()
// {
//     emit requestPasswordRecoveryPage();
// }
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
