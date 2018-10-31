/*!
 * \file server.h
 * Arquivo contendo a declaração da Interface Server.
 */

#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>

/*!
 * \class Server
 * \brief Clase para gerenciamento de servidor TCP.
 */
class Server : public QTcpServer{
    Q_OBJECT

protected:
    /*!
     * \brief Método para delegar o tratamento de uma conexão a uma thread trabalhadora auxiliar.
     *
     * Ao receber uma conexão o servidor delega o tratamento dela a um thread auxiliar e volta a escutar as transmissões.
     *
     * \param socketDescriptor Informações de configuração do socket.
     *
     * \sa WorkerThread.
     */
    virtual void incomingConnection(qintptr socketDescriptor) = 0;

};

#endif // SERVER_H
