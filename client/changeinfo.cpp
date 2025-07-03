// changeinfo.cpp
#include "changeinfo.h"
#include "ui_changeinfo.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QDebug>

ChangeInfo::ChangeInfo(SocketHandler* socketHandler, const QString &username, QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::ChangeInfo)
    , m_socketHandler(socketHandler)
    ,c_username(username)
{
    ui->setupUi(this);

    connect(ui->saveButton, &QPushButton::clicked,
            this, &ChangeInfo::onSaveClicked);
    connect(ui->cancelButton, &QPushButton::clicked,
            this, &ChangeInfo::onCancelClicked);

    if (m_socketHandler) {
        disconnect(m_socketHandler, &SocketHandler::messageReceived,nullptr, nullptr);
        connect(m_socketHandler, &SocketHandler::messageReceived,
                this, &ChangeInfo::onMessageReceived);
        disconnect(m_socketHandler, &SocketHandler::errorOccurred,nullptr, nullptr);
        connect(m_socketHandler, &SocketHandler::errorOccurred,
                this, &ChangeInfo::onErrorOccurred);

        requestUserInfo();
    } else {
        QMessageBox::critical(this, "Internal Error", "SocketHandler is null");
    }
}

ChangeInfo::~ChangeInfo()
{
    delete ui;
}

void ChangeInfo::requestUserInfo()
{
    QString msg = QString("4;%1").arg(c_username);
    qDebug() << "Requesting user info:" << msg;
    m_socketHandler->sendMessage(msg);
}

void ChangeInfo::loadUserInfoToUI()
{
    ui->firstNamelineEdit->setText(firstName);
    ui->lastNamelineEdit->setText(lastName);
    ui->emaillineEdit->setText(email);
    ui->phonelineEdit->setText(phoneNumber);
    ui->usernamelineEdit->setText(c_username);
    ui->passwordlineEdit->setText(password);

    qDebug() << "User info loaded to UI";
}

bool ChangeInfo::checkValidFirstName(const QString& fn) {
    return QRegularExpression("^[a-zA-Z]+$").match(fn).hasMatch();
}

bool ChangeInfo::checkValidLastName(const QString& ln) {
    return QRegularExpression("^[a-zA-Z]+$").match(ln).hasMatch();
}

bool ChangeInfo::checkValidUsername(const QString& us) {
    return QRegularExpression("^[a-zA-Z0-9]{4,}$").match(us).hasMatch();
}

bool ChangeInfo::checkValidEmail(const QString& em) {
    return QRegularExpression("^[\\w.-]+@gmail\\.com$").match(em).hasMatch();
}

bool ChangeInfo::checkValidPassword(const QString& pa) {
    return QRegularExpression("^[a-zA-Z0-9]{6,}$").match(pa).hasMatch();
}

bool ChangeInfo::checkValidPhone(const QString& ph) {
    return QRegularExpression("^98\\d{10}$").match(ph).hasMatch();
}


// bool ChangeInfo::validateInputs()
// {
//     QString fn = ui->firstNamelineEdit->text().trimmed();
//     QString ln = ui->lastNamelineEdit->text().trimmed();
//     QString em = ui->emaillineEdit->text().trimmed();
//     QString ph = ui->phonelineEdit->text().trimmed();
//     QString pa = ui->passwordlineEdit->text().trimmed();
//     QString us = ui->usernamelineEdit->text().trimmed();

//     if (!checkValidFirstName(fn)) {
//         QMessageBox::warning(this, "Validation Error", "First name must contain only letters.");
//         return false;
//     }
//     if (!checkValidLastName(ln)) {
//         QMessageBox::warning(this, "Validation Error", "Last name must contain only letters.");
//         return false;
//     }
//     if (!checkValidEmail(em)) {
//         QMessageBox::warning(this, "Validation Error", "Invalid email format.");
//         return false;
//     }
//     if (!checkValidPhone(ph)) {
//         QMessageBox::warning(this, "Validation Error", "Phone must start with 98 and contain 12 digits.");
//         return false;
//     }
//     // if (!checkValidPassword(pa)) {
//     //     QMessageBox::warning(this, "Validation Error", "Password must be at least 6 letters or digits.");
//     //     return false;
//     // }// server can not send me password of the user...
//     if (!checkValidUsername(us)) {
//         QMessageBox::warning(this, "Validation Error", "Username is not valid.");
//         return false;
//     }

//     return true;
// }

bool ChangeInfo::validateInputs()
{
    QString fn = ui->firstNamelineEdit->text().trimmed();
    QString ln = ui->lastNamelineEdit->text().trimmed();
    QString em = ui->emaillineEdit->text().trimmed();
    QString ph = ui->phonelineEdit->text().trimmed();
    QString pa = ui->passwordlineEdit->text().trimmed();
    QString us = ui->usernamelineEdit->text().trimmed();

    if (!checkValidFirstName(fn)) {
        QMessageBox::warning(this, "Validation Error", "First name must contain only letters.");
        return false;
    }
    if (!checkValidLastName(ln)) {
        QMessageBox::warning(this, "Validation Error", "Last name must contain only letters.");
        return false;
    }
    if (!checkValidEmail(em)) {
        QMessageBox::warning(this, "Validation Error", "Invalid email format.");
        return false;
    }
    if (!checkValidPhone(ph)) {
        QMessageBox::warning(this, "Validation Error", "Phone must start with 98 and contain 12 digits.");
        return false;
    }
    if (!checkValidUsername(us)) {
        QMessageBox::warning(this, "Validation Error", "Username is not valid.");
        return false;
    }

    // if the user do not enter the password the program do not change it
    if (!pa.isEmpty() && !checkValidPassword(pa)) {
        QMessageBox::warning(this, "Validation Error", "Password must be at least 6 letters or digits.");
        return false;
    }

    return true;
}


void ChangeInfo::onSaveClicked()
{
    if (!validateInputs())
        return;

    QString fn = ui->firstNamelineEdit->text().trimmed();
    QString ln = ui->lastNamelineEdit->text().trimmed();
    QString em = ui->emaillineEdit->text().trimmed();
    QString ph = ui->phonelineEdit->text().trimmed();
    QString us = ui->usernamelineEdit->text().trimmed();
    QString pa = ui->passwordlineEdit->text().trimmed();

    if(pa.isEmpty()){
        pa = password;
    }

    QString msg = QString("5;%1;%2;%3;%4;%5;%6;%7").arg(c_username, fn, ln, ph, em, us, pa);
    qDebug() << "Sending changeInfo:" << msg;
    m_socketHandler->sendMessage(msg);
}

void ChangeInfo::onCancelClicked()
{
    emit changeCancelled();
    this->close();
}

// void ChangeInfo::onMessageReceived(const QString& msg)
// {
//     qDebug() << "Server reply changeInfo:" << msg;

//     if (msg.contains(";") && msg.split(";").size() >= 6) {
//         QStringList parts = msg.split(";");
//         if (parts.size() >= 6) {
//             firstName = parts[0];
//             lastName = parts[1];
//             email = parts[2];
//             phoneNumber = parts[3];
//             // parts[4] = username
//             password = parts[5];
//             loadUserInfoToUI();
//             return;
//         }
//     }

//     if (msg.trimmed() == "1") {
//         QMessageBox::information(this, "Success", "Information updated successfully!");
//         emit infoChanged();
//         this->close();
//     }
//     else if (msg.trimmed() == "0") {
//         QMessageBox::warning(this, "Failed", "Update failed. Please try again.");
//     }
//     else {
//         QMessageBox::warning(this, "Error", "Server error: " + msg);
//     }
// }

void ChangeInfo::onMessageReceived(const QString& msg)
{
    qDebug() << "Server reply changeInfo:" << msg;

    if (msg.contains(";")) {
        QStringList parts = msg.split(";");

        if (parts.size() >= 6) {
            firstName = parts[0];
            lastName = parts[1];
            email = parts[2];
            phoneNumber = parts[3];
            // password = part[4]; // if the user do not enter nothing the program do not change the password
            password = parts[5];

            qDebug() << "User info received - FirstName:" << firstName
                     << "LastName:" << lastName << "Email:" << email;

            loadUserInfoToUI();
            return;
        }
    }

    QString trimmedMsg = msg.trimmed();
    if (trimmedMsg == "1") {
        QMessageBox::information(this, "Success", "Information updated successfully!");
        emit infoChanged();
        this->close();
    }
    else if (trimmedMsg == "0") {
        QMessageBox::warning(this, "Failed", "Update failed. Please try again.");
    }
    // else {
    //     qDebug() << "Unknown server response:" << msg;
    //     QMessageBox::warning(this, "Error", "Unexpected server response: " + msg);
    // }
}


// void ChangeInfo::onMessageReceived(const QString& msg)
// {
//     qDebug() << "Server reply changeInfo:" << msg;
//     if (msg == "1") {
//         QMessageBox::information(this, "Success", "Information updated successfully.");
//         emit infoChanged();
//         this->close();
//     } else {
//         QMessageBox::warning(this, "Failed", "Connection Problem");
//     }
// }

void ChangeInfo::onErrorOccurred(const QString& err)
{
    QMessageBox::critical(this, "Network Error", err);
}
