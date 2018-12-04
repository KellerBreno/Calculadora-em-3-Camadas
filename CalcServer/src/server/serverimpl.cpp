/*!
 * \file serverimpl.cpp
 * Arquivo contendo a implementação da Classe ServerImpl.
 */

#include "serverimpl.h"
#include "workertaskimpl.h"
#include "database/databasehelperimpl.h"

/*!
 * \brief Construtor padrão da classe ServerImpl.
 *
 * Demanda a configuração do Server para a classe pai e instância um helper de acesso ao banco de dados.
 *
 * \param parent Referência ao componente pai.
 */
ServerImpl::ServerImpl(QObject *parent) : QTcpServer(parent){
    databaseHelper = new DatabaseHelperImpl();
    threadPool = QThreadPool::globalInstance();
}

ServerImpl::ServerImpl(const ServerImpl& rhs){
    databaseHelper = rhs.databaseHelper;
}

ServerImpl& ServerImpl::operator=(const ServerImpl& rhs){
    if(&rhs == this){
        return *this;
    }
    databaseHelper = rhs.databaseHelper;
    return *this;
}

/*!
 * \brief Destrutor da classe ServerImpl.
 *
 * Apaga a referência ao helper de acesso ao banco de dados.
 *
 */
ServerImpl::~ServerImpl(){
    delete databaseHelper;
}

void ServerImpl::incomingConnection(qintptr socketDescriptor){
    WorkerTask *task = new WorkerTaskImpl(socketDescriptor, this, databaseHelper);
    QRunnable* runnable = task->getRunnable();
    runnable->setAutoDelete(true);
    threadPool->start(runnable);
}

bool ServerImpl::listen(){
    return QTcpServer::listen();
}

QString ServerImpl::errorString() const{
    return QTcpServer::errorString();
}

quint16	ServerImpl::serverPort() const{
    return QTcpServer::serverPort();
}
