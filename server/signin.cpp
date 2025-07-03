#include "signin.h"

signin::signin()
{}

QString signin::check(const QString &username, const QString &password)
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
        QByteArray byteArray = password.toUtf8();
        QByteArray hash = QCryptographicHash::hash(byteArray, QCryptographicHash::Sha256);
        QString passHash = QString(hash.toHex());;
        if((usersList[username].toObject())["password"].toString()==passHash)
        {
            return "1";
        }
        else
        {
            return "0";
        }
    }
    else
    {
        return "0";
    }
}
