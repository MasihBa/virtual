#ifndef PASSRECOVERY_H
#define PASSRECOVERY_H

#include <QObject>
#include <QFile>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>

class PassRecovery : public QObject
{
    Q_OBJECT
public:
    explicit PassRecovery(QObject *parent = nullptr);
    QString check(const QString& username,const QString& phoneNumber);
signals:
};

#endif // PASSRECOVERY_H
