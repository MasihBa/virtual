#include "passrecovery.h"

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
