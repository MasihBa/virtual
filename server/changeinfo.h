#ifndef CHANGEINFO_H
#define CHANGEINFO_H

#include <QObject>

class ChangeInfo : public QObject
{
    Q_OBJECT
public:
    explicit ChangeInfo(QObject *parent = nullptr);
    QString updateInfo(const QString& name,const QString& lastName,const QString& phoneNumber,const QString& email,const QString& username,const QString& password);
signals:
};

#endif // CHANGEINFO_H
