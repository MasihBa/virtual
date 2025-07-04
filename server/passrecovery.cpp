#include "passrecovery.h"
#include <QCryptographicHash>

PassRecovery::PassRecovery(QObject *parent)
    : QObject{parent}
{}

QString PassRecovery::check(const QString &username, const QString &phoneNumber)
{
    QFile users("users.json");
    if (!users.open(QIODevice::ReadOnly)) {
        return "-1";
    }

    QByteArray data = users.readAll();
    users.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject usersList = doc.object();

    if(usersList.contains(username))
    {
        if((usersList[username].toObject())["phoneNumber"].toString()==phoneNumber)
        {
            return "1";
        }
        else
        {
            return "0";
        }
    }
    else{
        return "0";
    }
}

void PassRecovery::changePassword(const QString& password ,const QString &username, const QString &phoneNumber)
{
    QFile users("users.json");
    QJsonObject usersList,newInfo;
    if (users.open(QIODevice::ReadOnly)) {
        QByteArray data = users.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        usersList = doc.object();
        users.close();
    }

    newInfo["name"] = (usersList[username].toObject())["name"].toString();
    newInfo["lastname"] = (usersList[username].toObject())["lastname"].toString();
    newInfo["email"] = (usersList[username].toObject())["email"].toString();
    newInfo["phoneNumber"] = (usersList[username].toObject())["phoneNumber"].toString();
    QByteArray byteArray = password.toUtf8();
    QByteArray hash = QCryptographicHash::hash(byteArray, QCryptographicHash::Sha256);
    newInfo["password"] = QString(hash.toHex());
    usersList[username] = newInfo;
    if (users.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QJsonDocument updatedDoc(usersList);
        users.write(updatedDoc.toJson(QJsonDocument::Indented));
        users.close();
    }
}
