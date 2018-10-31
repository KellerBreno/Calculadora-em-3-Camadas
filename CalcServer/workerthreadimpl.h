/*!
 * \file workerthreadimpl.h
 * Arquivo contendo a declaração da Classe WorkerThreadImpl.
 */

#ifndef WORKERTHREADIMPL_H
#define WORKERTHREADIMPL_H

#include <QTcpSocket>

#include "databasehelper.h"
#include "workerthread.h"

/*!
 * \class WorkerThreadImpl
 * \brief Implementação da interface WorkerThread para realização de operações do servidor em uma thread.
 */
class WorkerThreadImpl : public WorkerThread {
    Q_OBJECT

    /*!
     * \brief Classe de Testes para WorkerThread
     */
    friend class OperacoesTest;

public:
    WorkerThreadImpl(qintptr socketDescriptor, QObject *parent, DatabaseHelper *databaseHelper);
    virtual ~WorkerThreadImpl() override;
    virtual void run() override;

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
    qintptr socketDescriptor;

    /*!
     * \brief Referência ao helper de acesso ao banco de dados.
     */
    DatabaseHelper *databaseHelper;

private:
    /*!
     * \brief Construtor de Cópia.
     * \param rhs Objeto a ser copiado.
     */
    WorkerThreadImpl(const WorkerThreadImpl& rhs){}

    /*!
     * \brief Sobrecarga do operador =.
     * \param rhs Objeto a ser copiado.
     * \return Novo objeto copiado.
     */
    WorkerThreadImpl& operator=(const WorkerThreadImpl& rhs){}

    WorkerThreadImpl();
    QJsonObject handleMessage(QJsonObject jsonObject);
    QJsonObject handleAuthenticate(QJsonObject jsonObject);
    QJsonObject handleOperation(QJsonObject jsonObject);
    QJsonObject handleUserReport(QJsonObject jsonObject);
    QJsonObject handleAllUsersReport(QJsonObject jsonObject);
};

#endif // WORKERTHREADIMPL_H
