/*!
 * \file workerthread.h
 * Arquivo contendo a declaração da Classe WorkerThread.
 */

#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>
#include <QTcpSocket>

#include "databasehelper.h"

/*!
 * \class WorkerThread
 * \brief Classe para realização de operações do servidor em uma thread.
 */
class WorkerThread : public QThread {
    Q_OBJECT

    /*!
     * \brief Classe de Testes para WorkerThread
     */
    friend class OperacoesTest;

public:
    WorkerThread(int socketDescriptor, QObject *parent, DatabaseHelper *databaseHelper);
    virtual ~WorkerThread();
    void run() override;

signals:
    /*!
     * \brief Signal utilizado para sinalizar erros.
     * \param socketError Tipo do erro detectado.
     */
    void error(QTcpSocket::SocketError socketError);

protected:
    /*!
     * \brief Contém as informações de configuração do socket.
     */
    int socketDescriptor;

    /*!
     * \brief Referência ao helper de acesso ao banco de dados.
     */
    DatabaseHelper *databaseHelper;

private:
    /*!
     * \brief Construtor de Cópia.
     * \param rhs Objeto a ser copiado.
     */
    WorkerThread(const WorkerThread& rhs){}

    /*!
     * \brief Sobrecarga do operador =.
     * \param rhs Objeto a ser copiado.
     * \return Novo objeto copiado.
     */
    WorkerThread& operator=(const WorkerThread& rhs){}

    WorkerThread();
    QJsonObject handleMessage(QJsonObject jsonObject);
    QJsonObject handleAuthenticate(QJsonObject jsonObject);
    QJsonObject handleOperation(QJsonObject jsonObject);
    QJsonObject handleUserReport(QJsonObject jsonObject);
    QJsonObject handleAllUsersReport(QJsonObject jsonObject);
};

#endif // WORKERTHREAD_H
