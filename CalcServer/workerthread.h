#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>
#include <QTcpSocket>

#include "databasehelper.h"

class WorkerThread : public QThread {
    Q_OBJECT

public:
    WorkerThread(int socketDescriptor, QObject *parent, DatabaseHelper *databaseHelper);
    void run() override;

signals:
    void error(QTcpSocket::SocketError socketError);

protected:
    int socketDescriptor;
    DatabaseHelper *databaseHelper;

private:
    WorkerThread(const WorkerThread& rhs){}
    WorkerThread& operator=(const WorkerThread& rhs){}
};

#endif // WORKERTHREAD_H
