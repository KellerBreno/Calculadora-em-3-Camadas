/*!
 * \file serverimpl.h
 * Arquivo contendo a declaração da Classe ServerImpl.
 */

#ifndef SERVERIMPL_H
#define SERVERIMPL_H

#include "databasehelper.h"
#include "server.h"

/*!
 * \class ServerImpl
 * \brief Implementação da interface Server.
 */
class ServerImpl : public Server{
    Q_OBJECT

public:
    ServerImpl(QObject *parent = nullptr);
    virtual ~ServerImpl() override;

protected:
    void incomingConnection(qintptr socketDescriptor) override;

    /*!
     * \brief Referência ao helper de acesso ao banco de dados.
     */
    DatabaseHelper *databaseHelper;
};

#endif // SERVERIMPL_H
