#ifndef ROLE_H
#define ROLE_H

#include <QString>

class User;

class Role{
public:
    virtual QString getRoleName() = 0;
    virtual User* getUser() = 0;
    virtual void setUser(User* user) = 0;
};

#endif // ROLE_H
