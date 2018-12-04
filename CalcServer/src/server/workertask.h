/*!
 * \file workerthread.h
 * Arquivo contendo a declaração da Interface WorkerThread.
 */

#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QObject>
#include <QRunnable>

/*!
 * \class WorkerThread
 * \brief Interface para thread de trabalho auxiliar.
 */
class WorkerTask{
public:
    /*!
     * \brief Método para delegação do tratamento de uma mensagem recebida e envio da respostas.
     *
     * Este método recebe um byte array correspondente a um objeto JSON, após isso cria um objeto JSON e delega a resolução da mensagem para o
     * método handlMessage. Por fim, recebe a resposta da mensagem, codifica ela e envia ao cliente pela rede.
     *
     * \sa WorkerThreadImpl::handleMessage(QJsonObject), WorkerThreadImpl::error(QTcpSocket::SocketError).
     */
    virtual void run() = 0;

    virtual QRunnable* getRunnable() = 0;
};

#endif // WORKERTHREAD_H
