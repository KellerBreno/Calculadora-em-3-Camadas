/*!
 * \file basicuserimpl.h
 * Arquivo contendo a Declaração da Classe BasicUserImpl
 */

#ifndef BASICUSERIMPL_H
#define BASICUSERIMPL_H

#include "basicuser.h"
#include "user.h"

/*!
 * \class BasicUserImpl
 * \brief Implementação da interface BasicUser
 */
class BasicUserImpl : public BasicUser{
public:
    BasicUserImpl();
    virtual QString getRoleName() override;
    virtual User* getUser() override;
    virtual void setUser(User* user) override;
    virtual QString getUsername() override;
    virtual QString getPassword() override;

private:
    /*!
     * \brief Ponteiro para o usuário correspondente a este papel
     */
    User *user;

};

#endif // BASICUSERIMPL_H
