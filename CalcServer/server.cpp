#include "server.h"
#include "workerthread.h"
#include "databasehelperimpl.h"

Server::Server(QObject *parent) : QTcpServer(parent){
    databaseHelper = new DatabaseHelperImpl();
}

Server::~Server(){
    delete databaseHelper;
}

void Server::incomingConnection(qintptr socketDescriptor){
    WorkerThread *thread = new WorkerThread(socketDescriptor, this, databaseHelper);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}
