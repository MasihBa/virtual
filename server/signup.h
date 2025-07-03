#ifndef SIGNUP_H
#define SIGNUP_H

#include <QString>

class signup
{
public:
    explicit signup();
    QString registeration(const QString& name,const QString& lastName,const QString& phoneNumber,const QString& email,const QString& username,const QString& password);
    // return 1->Registration was successful. 0->The username is duplicated. -1->There was a problem reading or writing the file.
};

#endif // SIGNUP_H
