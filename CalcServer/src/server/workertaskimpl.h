/*!
 * \file workerthreadimpl.h
 * Arquivo contendo a declaração da Classe WorkerThreadImpl.
 */

#ifndef WORKERTASKIMPL_H
#define WORKERTASKIMPL_H

#include <QTcpSocket>
#include <QRunnable>

#include "database/databasehelper.h"
#include "server.h"
#include "workertask.h"

/*!
 * \class WorkerThreadImpl
 * \brief Implementação da interface WorkerThread para realização de operações do servidor em uma thread.
 */
class WorkerTaskImpl :public QRunnable, public WorkerTask {

    /*!
     * \brief Classe de Testes para WorkerThread
     */
    friend class OperacoesTest;

public:
    WorkerTaskImpl(qintptr socketDescriptor, QObject *parent, DatabaseHelper *databaseHelper);
    virtual ~WorkerTaskImpl() override;
    virtual void run() override;
    virtual QRunnable* getRunnable() override;

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
    WorkerTaskImpl(const WorkerTaskImpl& rhs);

    /*!
     * \brief Sobrecarga do operador =.
     * \param rhs Objeto a ser copiado.
     * \return Novo objeto copiado.
     */
    WorkerTaskImpl& operator=(const WorkerTaskImpl& rhs);

    WorkerTaskImpl();
    QJsonObject handleMessage(QJsonObject jsonObject);
    QJsonObject handleAuthenticate(QJsonObject jsonObject);
    QJsonObject handleOperation(QJsonObject jsonObject);
    QJsonObject handleUserReport(QJsonObject jsonObject);
    QJsonObject handleAllUsersReport(QJsonObject jsonObject);
};

#endif // WORKERTASKIMPL_H
