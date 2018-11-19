#ifndef ADMINUSER_H
#define ADMINUSER_H

#include "role.h"

class AdminUser : public Role{
public:
    virtual QString getUsername() = 0;
    static const QString ADMIN_USER_NAME;
};

#endif // ADMINUSER_H
