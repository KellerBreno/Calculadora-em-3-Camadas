#ifndef BASICUSERIMPL_H
#define BASICUSERIMPL_H

#include "basicuser.h"
#include "user.h"

class BasicUserImpl : public BasicUser{
public:
    BasicUserImpl();
    virtual QString getRoleName() override;
    virtual User* getUser() override;
    virtual void setUser(User* user) override;
    virtual QString getUsername() override;
    virtual QString getPassword() override;

private:
    User *user;

};

#endif // BASICUSERIMPL_H
