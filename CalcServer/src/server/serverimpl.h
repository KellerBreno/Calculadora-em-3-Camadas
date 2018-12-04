/*!
 * \file serverimpl.h
 * Arquivo contendo a declaração da Classe ServerImpl.
 */

#ifndef SERVERIMPL_H
#define SERVERIMPL_H

#include "database/databasehelper.h"
#include "server.h"
#include <QTcpServer>
#include <QThreadPool>

/*!
 * \class ServerImpl
 * \brief Implementação da interface Server.
 */
class ServerImpl : public QTcpServer, public Server{
    Q_OBJECT

public:
    ServerImpl(QObject *parent = nullptr);
    virtual ~ServerImpl() override;
    virtual bool listen() override;
    virtual QString errorString() const override;
    virtual quint16	serverPort() const override;

protected:
    void incomingConnection(qintptr socketDescriptor) override;

    /*!
     * \brief Referência ao helper de acesso ao banco de dados.
     */
    DatabaseHelper *databaseHelper;

    /*!
     * \brief Construtor de Cópia.
     * \param rhs Objeto a ser copiado.
     */
    ServerImpl(const ServerImpl& rhs);

    /*!
     * \brief Sobrecarga do operador =.
     * \param rhs Objeto a ser copiado.
     * \return Novo objeto copiado.
     */
    ServerImpl& operator=(const ServerImpl& rhs);

    QThreadPool *threadPool;
};

#endif // SERVERIMPL_H
