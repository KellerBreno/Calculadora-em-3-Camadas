/*!
 * \file serverimpl.cpp
 * Arquivo contendo a implementação da Classe ServerImpl.
 */

#include "serverimpl.h"
#include "workerthreadimpl.h"
#include "databasehelperimpl.h"

/*!
 * \brief Construtor padrão da classe ServerImpl.
 *
 * Demanda a configuração do Server para a classe pai e instância um helper de acesso ao banco de dados.
 *
 * \param parent Referência ao componente pai.
 */
ServerImpl::ServerImpl(QObject *parent){
    this->setParent(parent);
    databaseHelper = new DatabaseHelperImpl();
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
    WorkerThread *thread = new WorkerThreadImpl(socketDescriptor, this, databaseHelper);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}
