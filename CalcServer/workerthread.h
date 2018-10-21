#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>
#include <QTcpSocket>

#include "databasehelper.h"

class WorkerThread : public QThread {
    Q_OBJECT

    friend class OperacoesTest;

public:
    WorkerThread(int socketDescriptor, QObject *parent, DatabaseHelper *databaseHelper);
    virtual ~WorkerThread();
    void run() override;

signals:
    void error(QTcpSocket::SocketError socketError);

protected:
    int socketDescriptor;
    DatabaseHelper *databaseHelper;

private:
    WorkerThread(const WorkerThread& rhs){}
    WorkerThread& operator=(const WorkerThread& rhs){}
    void trataMensagem(QString message, QTcpSocket tcpSocket);

    WorkerThread();
    QJsonObject menu(QJsonObject jsonObject);
    QJsonObject opcao1(QJsonObject jsonObject);
    QJsonObject opcao2(QJsonObject jsonObject);
    QJsonObject opcao3(QJsonObject jsonObject);
    QJsonObject opcao4(QJsonObject jsonObject);
};

#endif // WORKERTHREAD_H
