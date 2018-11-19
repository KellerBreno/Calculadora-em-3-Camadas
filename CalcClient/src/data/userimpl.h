#ifndef USERIMPL_H
#define USERIMPL_H

#include "user.h"
#include "role.h"
#include <vector>

using namespace std;

class UserImpl: public User{
public:
    UserImpl();
    virtual QString getUsername() override;
    virtual void setUsername(QString username) override;
    virtual QString getPassword() override;
    virtual void setPassword(QString password) override;
    virtual void addRole(Role *role) override;
    virtual Role* asRole(QString name) override;

private:
    QString username;
    QString password;
    vector<Role*> roles;
};

#endif // USERIMPL_H
