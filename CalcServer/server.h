#ifndef SERVER_H
#define SERVER_H

#include "databasehelper.h"

#include <QTcpServer>

class Server : public QTcpServer{
    Q_OBJECT

public:
    Server(QObject *parent = 0);
    virtual ~Server();

protected:
    void incomingConnection(qintptr socketDescriptor) override;
    DatabaseHelper *databaseHelper;
};

#endif // SERVER_H
