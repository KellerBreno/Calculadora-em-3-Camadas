/*!
 * \file basicuser.h
 * Arquivo contendo a Declaração da Interface BasicUser
 */

#ifndef BASICUSER_H
#define BASICUSER_H

#include "role.h"

/*!
 * \class BasicUser
 * \brief Interface correspondente ao papel usuário
 */
class BasicUser : public Role{
public:

    /*!
     * \brief Acessa o nome do usuário
     * \return Nome do usuário
     */
    virtual QString getUsername() = 0;

    /*!
     * \brief Acessa a senha do usuário
     * \return Senha do usuário
     */
    virtual QString getPassword() = 0;

    /*!
     * \brief Nome do papel "Usuário"
     */
    static const QString BASIC_USER_NAME;
};

#endif // BASICUSER_H
