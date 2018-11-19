#ifndef ADMINUSERIMPL_H
#define ADMINUSERIMPL_H

#include "adminuser.h"
#include "user.h"

class AdminUserImpl: public AdminUser{
public:
    AdminUserImpl();
    virtual QString getUsername() override;
    virtual QString getRoleName() override;
    virtual User* getUser() override;
    virtual void setUser(User* user) override;

private:
    User *user;
};

#endif // ADMINUSERIMPL_H
