/*!
 * \file adminuserimpl.h
 * Arquivo contendo a Declaração da Classe AdminUserImpl
 */

#ifndef ADMINUSERIMPL_H
#define ADMINUSERIMPL_H

#include "adminuser.h"
#include "user.h"

/*!
 * \class AdminUserImpl
 * \brief Implementação da Interface AdminUser
 */
class AdminUserImpl: public AdminUser{
public:
    AdminUserImpl();
    virtual QString getUsername() override;
    virtual QString getRoleName() override;
    virtual User* getUser() override;
    virtual void setUser(User* user) override;

private:
    /*!
     * \brief Ponteiro para o usuário correspondente a este papel
     */
    User *user;
};

#endif // ADMINUSERIMPL_H
