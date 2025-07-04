#ifndef GETUSERINFO_H
#define GETUSERINFO_H

#include <QFile>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>

class getUserInfo
{

public:
    getUserInfo();
    QString getInfo(const QString& username);

};

#endif // GETUSERINFO_H
