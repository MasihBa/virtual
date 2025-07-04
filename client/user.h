// user.h
#ifndef USER_H
#define USER_H

#include <QString>

struct User {
    QString firstName;
    QString lastName;
    QString email;
    QString phoneNumber;
    QString username;
    QString password;
};

extern User currentUser;

#endif // USER_H
