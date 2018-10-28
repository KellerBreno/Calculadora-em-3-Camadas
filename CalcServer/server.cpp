/*!
 * \file server.cpp
 * Arquivo contendo a implementação da Classe Server.
 */

#include "server.h"
#include "workerthread.h"
#include "databasehelperimpl.h"

/*!
 * \brief Construtor padrão da classe Server.
 *
 * Demanda a configuração do Server para a classe pai e instância um helper de acesso ao banco de dados.
 *
 * \param parent Referência ao componente pai.
 */
Server::Server(QObject *parent) : QTcpServer(parent){
    databaseHelper = new DatabaseHelperImpl();
}

/*!
 * \brief Destrutor da classe Server.
 *
 * Apaga a referência ao helper de acesso ao banco de dados.
 *
 */
Server::~Server(){
    delete databaseHelper;
}

/*!
 * \brief Método para delegar o tratamento de uma conexão a uma thread trabalhadora auxiliar.
 *
 * \param socketDescriptor Informações de configuração do socket.
 */
void Server::incomingConnection(qintptr socketDescriptor){
    WorkerThread *thread = new WorkerThread(socketDescriptor, this, databaseHelper);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}
