#ifndef SIGNIN_H
#define SIGNIN_H

#include <QFile>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QCryptographicHash>
class signin
{
public:
    explicit signin();
    QString check(const QString& username,const QString& password);
    // return 1->signIn was successful. -1->There was a problem reading the file.
};

#endif // SIGNIN_H
