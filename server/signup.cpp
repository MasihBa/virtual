#include "signup.h"
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QCryptographicHash>

signup::signup()
{

}

QString signup::registeration(const QString &name, const QString &lastName, const QString &phoneNumber, const QString &email, const QString &username, const QString &password)
{
    QFile users("users.json");
    QJsonObject newUsers,newUser;
    if (users.open(QIODevice::ReadOnly)) {
        QByteArray data = users.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        newUsers = doc.object();
        users.close();
    }

    if(newUsers.contains(username))
    {
        return "0";
    }

    newUser["name"] = name;
    newUser["lastname"] = lastName;
    newUser["email"] = email;
    newUser["phoneNumber"] = phoneNumber;
    QByteArray byteArray = password.toUtf8();
    QByteArray hash = QCryptographicHash::hash(byteArray, QCryptographicHash::Sha256);
    newUser["password"] = QString(hash.toHex());

    newUsers.insert(username,newUser);
    if (users.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QJsonDocument updatedDoc(newUsers);
        users.write(updatedDoc.toJson(QJsonDocument::Indented));
        users.close();
        return "1";
    }
    return "-1";
}
