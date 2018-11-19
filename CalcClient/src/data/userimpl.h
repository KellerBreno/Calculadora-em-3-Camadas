/*!
 * \file userimpl.h
 * Arquivo contendo a Declaração da Classe UserImpl
 */

#ifndef USERIMPL_H
#define USERIMPL_H

#include "user.h"
#include "role.h"
#include <vector>

using namespace std;

/*!
 * \class UserImpl
 * \brief Implementação da interface User
 */
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
    /*!
     * \brief Nome do usuário
     */
    QString username;

    /*!
     * \brief Senha do usuário
     */
    QString password;

    /*!
     * \brief Array contendo os papeis do usuário
     */
    vector<Role*> roles;
};

#endif // USERIMPL_H
