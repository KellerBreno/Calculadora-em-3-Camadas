/*!
 * \file user.h
 * Arquivo contendo a Declaração da Interface User
 */

#ifndef USER_H
#define USER_H

#include <QString>

class Role;

/*!
 * \class User
 * \brief Interface correspondente a qualquer usuário do sistema
 */
class User{
public:
    /*!
     * \brief Consulta o nome do usuário
     * \return Nome do usuário
     */
    virtual QString getUsername() = 0;

    /*!
     * \brief Altera o nome do usuário
     * \param username Nome do usuário
     */
    virtual void setUsername(QString username) = 0;

    /*!
     * \brief Consulta a senha do usuário
     * \return Senha do usuário
     */
    virtual QString getPassword() = 0;

    /*!
     * \brief Altera o nome do usuário
     * \param password Senha do usuário
     */
    virtual void setPassword(QString password) = 0;

    /*!
     * \brief Adiciona um novo papel ao usuário, caso ele já não tenha essa atribuição
     * \param role Novo papel do usuário
     */
    virtual void addRole(Role *role) = 0;

    /*!
     * \brief Retorna o papel correspondente ao name solicitado
     * \param name Nome do papel
     * \return Papel correspondente
     */
    virtual Role* asRole(QString name) = 0;
};

#endif // USER_H
