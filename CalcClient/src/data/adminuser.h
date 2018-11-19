/*!
 * \file adminuser.h
 * Arquivo contendo a Declaração da Interface AdminUser
 */

#ifndef ADMINUSER_H
#define ADMINUSER_H

#include "role.h"

/*!
 * \class AdminUser
 * \brief Interface correspondente ao papel de administrador do sistema
 */
class AdminUser : public Role{
public:
    /*!
     * \brief Método para acessa o nome do usuário correspondente
     * \return Nome do usuário
     */
    virtual QString getUsername() = 0;

    /*!
     * \brief Nome do papel "Administrador"
     */
    static const QString ADMIN_USER_NAME;
};

#endif // ADMINUSER_H
