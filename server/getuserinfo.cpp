#include "getuserinfo.h"

getUserInfo::getUserInfo() {}

QString getUserInfo::getInfo(const QString &username)
{
    QFile users("users.json");
    if (!users.open(QIODevice::ReadOnly)) {
        return "-1;0";
    }

    QByteArray data = users.readAll();
    users.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject usersList = doc.object();

    QString info;
    info = "2;" + (usersList[username].toObject())["name"].toString()+";"+(usersList[username].toObject())["lastname"].toString()+";"+(usersList[username].toObject())["email"].toString()+";"+(usersList[username].toObject())["phoneNumber"].toString();
    return info;
}
