// // findpassword.cpp
// #include "findpassword.h"
// #include "ui_findpassword.h"

// #include <QMessageBox>
// #include <QRegularExpression>
// #include <QDebug>
// FindPassword::FindPassword(SocketHandler* socketHandler, QMainWindow *parent)
//     : QMainWindow(parent),
//     ui(new Ui::FindPassword),
//     m_socketHandler(socketHandler)
// {
//     ui->setupUi(this);

//     connect(ui->passwordRecoverypushButton, &QPushButton::clicked,
//             this, &FindPassword::onPasswordRecoveryClicked);

//     if (m_socketHandler) {
//         connect(m_socketHandler, &SocketHandler::messageReceived,
//                 this, &FindPassword::onMessageReceived);
//     } else {
//         ui->passwordRecoverypushButton->setEnabled(false);
//         QMessageBox::critical(this, "Internal Error", "SocketHandler is null");
//     }
// }

// FindPassword::~FindPassword()
// {
//     delete ui;
//     m_socketHandler = nullptr;
// }

// bool FindPassword::checkValidUsername(const QString& username)
// {
//     static const QRegularExpression re("^[a-zA-Z0-9]{4,}$");
//     return re.match(username).hasMatch();
// }

// bool FindPassword::checkValidPhoneNumber(const QString& phoneNumber)
// {
//     static const QRegularExpression re("^\\d{10,14}$");
//     return re.match(phoneNumber).hasMatch();
// }

// void FindPassword::onPasswordRecoveryClicked()
// {
//     const QString username    = ui->passwordRecoveryUsernamelineEdit->text().trimmed();
//     const QString phoneNumber = ui->passwordRecoveryPhoneNumberlineEdit->text().trimmed();

//     if (!checkValidUsername(username)) {
//         QMessageBox::warning(this, "Invalid Username", "Invalid username format.");
//         return;
//     }

//     if (!checkValidPhoneNumber(phoneNumber)) {
//         QMessageBox::warning(this, "Invalid Phone", "Invalid phone number.");
//         return;
//     }

//     const QString message = QStringLiteral("3%1;%2").arg(username, phoneNumber);
//     qDebug() << "Sending:" << message;

//     if (m_socketHandler) {
//         m_socketHandler->sendMessage(message);
//         QMessageBox::information(this, "Success", "Request sent.");
//         emit backToSignIn();
//     } else {
//         QMessageBox::critical(this, "Error", "Socket not available.");
//     }
// }

// void FindPassword::onMessageReceived(const QString& msg)
// {
//     if (msg == QLatin1String("PasswordRecoverySuccess")) {
//         QMessageBox::information(this, "Success", "Check your inbox.");
//         emit backToSignIn();
//     } else {
//         qDebug() << "Server said:" << msg;
//     }
// }
// findpassword.cpp
#include "findpassword.h"
#include "ui_findpassword.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QDebug>

FindPassword::FindPassword(SocketHandler* socketHandler, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FindPassword)
    , m_socketHandler(socketHandler)
{
    ui->setupUi(this);

    connect(ui->passwordRecoverypushButton, &QPushButton::clicked,
            this, &FindPassword::onPasswordRecoveryClicked);

    if (m_socketHandler) {
        connect(m_socketHandler, &SocketHandler::messageReceived,
                this, &FindPassword::onMessageReceived);
        connect(m_socketHandler, &SocketHandler::errorOccurred,
                this, &FindPassword::onErrorOccurred);
    } else {
        ui->passwordRecoverypushButton->setEnabled(false);
        QMessageBox::critical(this, "Internal Error", "SocketHandler is null");
    }
}

FindPassword::~FindPassword()
{
    delete ui;
}

bool FindPassword::checkValidUsername(const QString& username)
{
    return QRegularExpression("^[a-zA-Z0-9]{4,}$").match(username).hasMatch();
}

bool FindPassword::checkValidPhoneNumber(const QString& phoneNumber)
{
    return QRegularExpression("^98\\d{10}$").match(phoneNumber).hasMatch();
}

void FindPassword::onPasswordRecoveryClicked()
{
    const QString username    = ui->passwordRecoveryUsernamelineEdit->text().trimmed();
    const QString phoneNumber = ui->passwordRecoveryPhoneNumberlineEdit->text().trimmed();

    if (!checkValidUsername(username)) {
        QMessageBox::warning(this, "Invalid Username", "Invalid username format.");
        return;
    }

    if (!checkValidPhoneNumber(phoneNumber)) {
        QMessageBox::warning(this, "Invalid Phone", "Phone must start with 98 and contain 12 digits.");
        return;
    }

    QString message = QString("3,%1,%2").arg(username, phoneNumber);
    qDebug() << "Sending password recovery request:" << message;

    if (m_socketHandler->state() == QAbstractSocket::ConnectedState) {
        m_socketHandler->sendMessage(message);
    } else {
        QMessageBox::critical(this, "Connection Error", "Not connected to server.");
    }
}

void FindPassword::onMessageReceived(const QString& msg)
{
    qDebug() << "Server reply for recovery:" << msg;
    if (msg == "PasswordRecoverySuccess") {
        QMessageBox::information(this, "Success", "Recovery successful. Check your email.");
        emit recoveryCompleted();
        this->close();
    } else if (msg.startsWith("PasswordRecoveryFailed")) {
        QMessageBox::warning(this, "Recovery Failed", msg);
    }
}

void FindPassword::onErrorOccurred(const QString& errorString)
{
    qDebug() << "Socket error in FindPassword:" << errorString;
    QMessageBox::critical(this, "Network Error", errorString);
}
