/*!
 * \file role.h
 * Arquivo contendo a Declaração da Interface Role
 */

#ifndef ROLE_H
#define ROLE_H

#include <QString>

class User;

/*!
 * \class Role
 * \brief Superclasse correspondente aos papeis que podem ser assumidos no sistema
 */
class Role{
public:
    /*!
     * \brief Método para acessar o nome papel
     * \return Nome do papel
     */
    virtual QString getRoleName() = 0;

    /*!
     * \brief Método para acessar o usuário correspondente ao papel
     * \return Usuário associado ao papel
     */
    virtual User* getUser() = 0;

    /*!
     * \brief Método para associar um usuário a um papel
     * \param user Usuário a ser associado
     */
    virtual void setUser(User* user) = 0;
};

#endif // ROLE_H
