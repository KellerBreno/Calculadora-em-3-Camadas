#ifndef USER_H
#define USER_H

#include <QString>

class Role;

class User{
public:
    virtual QString getUsername() = 0;
    virtual void setUsername(QString username) = 0;
    virtual QString getPassword() = 0;
    virtual void setPassword(QString password) = 0;
    virtual void addRole(Role *role) = 0;
    virtual Role* asRole(QString name) = 0;
};

#endif // USER_H
