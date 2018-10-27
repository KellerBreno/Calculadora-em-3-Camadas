/*!
 * \file server.h
 * Arquivo contendo a declaração da Classe Server.
 */

#ifndef SERVER_H
#define SERVER_H

#include "databasehelper.h"

#include <QTcpServer>

/*!
 * \class Server
 * \brief Clase para gerenciamento de uma customização de QTcpServer.
 */
class Server : public QTcpServer{
    Q_OBJECT

public:
    Server(QObject *parent = 0);
    virtual ~Server();

protected:
    void incomingConnection(qintptr socketDescriptor) override;

    /*!
     * \brief Referência ao helper de acesso ao banco de dados.
     */
    DatabaseHelper *databaseHelper;
};

#endif // SERVER_H
