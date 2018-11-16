/*!
 * \file databasehelperimpl.h
 * Arquivo contendo a declaração da Classe DatabaseHelperImpl.
 */

#ifndef DATABASEHELPERIMPL_H
#define DATABASEHELPERIMPL_H

#include <QSqlDatabase>

#include "databasehelper.h"

/*!
 * \class DatabaseHelperImpl
 * \brief Implementação da Interface DatabaseHelper para acesso ao banco de dados SQLite
 */
class DatabaseHelperImpl : public DatabaseHelper{

    /*!
     * \brief Classe de Testes para DatabaseHelperImpl
     */
    friend class DatabaseHelperImplTest;

public:
    DatabaseHelperImpl();
    virtual ~DatabaseHelperImpl();
    virtual int getUserId(QString username);
    virtual bool insertOperation(int userId, double v1, QString operacao, double v2, double resultado);
    virtual vector<pair<QString, QString>> getAllUsers();
    virtual vector<pair<QString, int>> getOperationsByUser(QString username);
    virtual vector<pair<QString, int>> getAllOperations();
    virtual bool isAdmin(QString username);

protected:
    /*!
     * \brief Objeto de gerenciamento do banco de dados.
     */
    QSqlDatabase sqlDatabase;

private:
    /*!
     * \brief Construtor de Cópia.
     * \param rhs Objeto a ser copiado.
     */
    DatabaseHelperImpl(const DatabaseHelperImpl& rhs);

    /*!
     * \brief Sobrecarga do operador =.
     * \param rhs Objeto a ser copiado.
     * \return Novo objeto copiado.
     */
    DatabaseHelperImpl& operator=(const DatabaseHelperImpl& rhs);
    void setupDatabase();
};

#endif // DATABASEHELPERIMPL_H
