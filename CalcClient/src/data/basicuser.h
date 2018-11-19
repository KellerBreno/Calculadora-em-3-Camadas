#ifndef BASICUSER_H
#define BASICUSER_H

#include "role.h"

class BasicUser : public Role{
public:
    virtual QString getUsername() = 0;
    virtual QString getPassword() = 0;
    static const QString BASIC_USER_NAME;
};

#endif // BASICUSER_H
