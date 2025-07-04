#include "changeinfo.h"
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QCryptographicHash>

ChangeInfo::ChangeInfo(QObject *parent)
    : QObject{parent}
{}

QString ChangeInfo::updateInfo(const QString& oldUserName,const QString &name, const QString &lastName, const QString &phoneNumber, const QString &email, const QString &username, const QString &password)
{
    QFile users("users.json");
    QJsonObject usersList,newInfo;
    if (users.open(QIODevice::ReadOnly)) {
        QByteArray data = users.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        usersList = doc.object();
        users.close();
    }
    else{
        return "-1";
    }

    newInfo["name"] = name;
    newInfo["lastname"] = lastName;
    newInfo["email"] = email;
    newInfo["phoneNumber"] = phoneNumber;
    QByteArray byteArray = password.toUtf8();
    QByteArray hash = QCryptographicHash::hash(byteArray, QCryptographicHash::Sha256);
    newInfo["password"] = QString(hash.toHex());
    usersList.remove(oldUserName);
    usersList[username] = newInfo;
    if (users.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QJsonDocument updatedDoc(usersList);
        users.write(updatedDoc.toJson(QJsonDocument::Indented));
        users.close();
        return "1";
    }
    return "-1";
}
