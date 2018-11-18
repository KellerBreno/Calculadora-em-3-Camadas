/*!
 * \file databasehelper.h
 * Arquivo contendo a declaração da Interface DatabaseHelper.
 */

#ifndef DATABASEHELPER_H
#define DATABASEHELPER_H

#include <QString>

#include <utility>
#include <vector>

using namespace std;

/*!
 * \class DatabaseHelper
 * \brief Interface para acesso a um banco de dados.
 */
class DatabaseHelper{
public:
    /*!
     * \brief Esse método busca se um usuário está presente no banco de dados.
     * \param username Nome do usuário a ser buscado.
     * \return  O id do usuário no banco.
     */
    virtual int getUserId(QString username) = 0;

    /*!
     * \brief Esse método armazena um registro de operação.
     * \param userId Id do usuário que realizou a operação.
     * \param v1 Primeiro operando.
     * \param operacao Operação realizada.
     * \param v2 Segundo Operando.
     * \param resultado Resultado da operação.
     * \return Se a inserção foi realizada.
     */
    virtual bool insertOperation(int userId, double v1, QString operacao, double v2, double resultado) = 0;

    /*!
     * \brief Retorna todos os usuários do banco e seus respectivas senhas.
     * \return Lista de pares contendo nome de usuário e senha.
     */
    virtual vector<pair<QString, QString>> getAllUsers() = 0;

    /*!
     * \brief Gera uma tabela de sobre as operações realizadas pelo usuário.
     * \param username Nome do usuário a ser buscado.
     * \return Lista de pares contendo tipo de operação e quantidade de vezes que ela foi realizada.
     * \sa DatabaseHelper::getAllOperations().
     */
    virtual vector<pair<QString, int>> getOperationsByUser(QString username) = 0;

    /*!
     * \brief Gera uma tabela de sobre as operações realizadas por todos os usuários.
     * \return Lista de pares contendo tipo de operação e quantidade de vezes que ela foi realizada.
     * \sa DatabaseHelper::getOperationsByUser(QString).
     */
    virtual vector<pair<QString, int>> getAllOperations() = 0;

    /*!
     * \brief Verifica se um usuário tem permissõe de administrador.
     * \param username Nome do usuário a ser buscado.
     * \return Se o usuário é administrador.
     */
    virtual bool isAdmin(QString username) = 0;
};

#endif // DATABASEHELPER_H
