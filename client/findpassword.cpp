#include "findpassword.h"
#include "ui_findpassword.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QDebug>

FindPassword::FindPassword(SocketHandler* socketHandler, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FindPassword)
    , m_socketHandler(socketHandler)
    , m_isVerificationStep(true)
    , m_verifiedUsername("")
    , m_verifiedPhone("")
{
    ui->setupUi(this);

    connect(ui->passwordRecoverypushButton, &QPushButton::clicked,
            this, &FindPassword::onPasswordRecoveryClicked);

    if (m_socketHandler) {
        disconnect(m_socketHandler, &SocketHandler::messageReceived, nullptr, nullptr);
        connect(m_socketHandler, &SocketHandler::messageReceived,
                this, &FindPassword::onMessageReceived);
        disconnect(m_socketHandler, &SocketHandler::errorOccurred, nullptr, nullptr);
        connect(m_socketHandler, &SocketHandler::errorOccurred,
                this, &FindPassword::onErrorOccurred);
    } else {
        ui->passwordRecoverypushButton->setEnabled(false);
        QMessageBox::critical(this, "Internal Error", "SocketHandler is null");
    }

    ui->newPasswordLineEdit->setEnabled(false);
    ui->passwordRecoverypushButton->setText("Verify Identity");
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

bool FindPassword::checkValidPassword(const QString& password)
{
    return QRegularExpression("^[a-zA-Z0-9]{4,}$").match(password).hasMatch();
}

void FindPassword::onPasswordRecoveryClicked()
{
    if (m_isVerificationStep) {
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

        QString message = QString("-4;%1;%2").arg(username, phoneNumber);
        qDebug() << "Sending identity verification request:" << message;

        m_verifiedUsername = username;
        m_verifiedPhone = phoneNumber;

        if (m_socketHandler->state() == QAbstractSocket::ConnectedState) {
            m_socketHandler->sendMessage(message);
        } else {
            QMessageBox::critical(this, "Connection Error", "Not connected to server.");
        }
    } else {
        sendPasswordChangeRequest();
    }
}

void FindPassword::sendPasswordChangeRequest()
{
    const QString newPassword = ui->newPasswordLineEdit->text().trimmed();

    if (!checkValidPassword(newPassword)) {
        QMessageBox::warning(this, "Invalid Password",
                             "Password must contain only letters and numbers (minimum 4 characters).");
        return;
    }

    QString message = QString("3;%1;%2;%3").arg(m_verifiedUsername, m_verifiedPhone, newPassword);
    qDebug() << "Sending password change request:" << message;

    if (m_socketHandler->state() == QAbstractSocket::ConnectedState) {
        m_socketHandler->sendMessage(message);
    } else {
        QMessageBox::critical(this, "Connection Error", "Not connected to server.");
    }
}

void FindPassword::onMessageReceived(const QString& msg)
{
    qDebug() << "Server reply:" << msg;

    if (m_isVerificationStep) {
        if (msg == "1") {
            QMessageBox::information(this, "Identity Verified",
                                     "Identity verified successfully. Please enter your new password.");

            ui->newPasswordLineEdit->setEnabled(true);
            ui->passwordRecoveryUsernamelineEdit->setEnabled(false);
            ui->passwordRecoveryPhoneNumberlineEdit->setEnabled(false);
            ui->passwordRecoverypushButton->setText("Change Password");

            m_isVerificationStep = false;
        }
        else if (msg == "0") {
            QMessageBox::warning(this, "Error", "Phone number and username do not match.");
        }
        else if (msg == "-1") {
            QMessageBox::critical(this, "Error", "Error in identity verification.");
        }
        else {
            qDebug() << "Unknown verification response:" << msg;
            QMessageBox::warning(this, "Unknown Response", "Received unknown response from server.");
        }
    } else {
        if (msg == "1") {
            QMessageBox::information(this, "Password Changed", "Password changed successfully!");
            emit recoveryCompleted();
            this->close();
        }
        else if (msg == "0") {
            QMessageBox::warning(this, "Error", "Failed to change password. Please try again.");
        }
        else if (msg == "-1") {
            QMessageBox::critical(this, "Error", "Error in password change process.");
        }
        else {
            qDebug() << "Unknown password change response:" << msg;
            QMessageBox::warning(this, "Unknown Response", "Received unknown response from server.");
        }
    }
}

void FindPassword::onErrorOccurred(const QString& errorString)
{
    qDebug() << "Socket error in FindPassword:" << errorString;
    QMessageBox::critical(this, "Network Error", errorString);
}
