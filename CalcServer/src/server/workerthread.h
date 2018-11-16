/*!
 * \file workerthread.h
 * Arquivo contendo a declaração da Interface WorkerThread.
 */

#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QObject>

/*!
 * \class WorkerThread
 * \brief Interface para thread de trabalho auxiliar.
 */
class WorkerThread{
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

    /*!
     * \brief Método para o inicio de execução de uma WorkerThread.
     * \sa WorkerThreadImpl::finished().
     */
    virtual void start() = 0;

    /*!
     * \brief Representa o fim de execução de WorkerThread.
     */
    virtual void finished() = 0;

    /*!
     * \brief Responsavel por desalocar elementos da WorkerThread.
     */
    virtual void deleteLater() = 0;

    /*!
     * \brief Método retorna uma referência a um objeto QObject correspondente a essa classe.
     * \return Referencia ao QObject correspondente a classe.
     */
    virtual QObject* getQObject() = 0;
};

#endif // WORKERTHREAD_H
