#ifndef NETWORKMANAGERIMPL_H
#define NETWORKMANAGERIMPL_H

#include "networkmanager.h"

#include <QTcpSocket>

class NetworkManagerImpl : public QObject, public NetworkManager{
    Q_OBJECT
public:
    NetworkManagerImpl();
    virtual ~NetworkManagerImpl();
    virtual void configure(QString ip, quint16 port) override;
    virtual void login(QString username, QString password) override;
    virtual void doOperation(QString username, double factor1, double factor2, int opCode) override;
    virtual void reportByUser(QString username) override;
    virtual void reportAllUsers(QString username) override;
    virtual QObject* getQObject() override;

public slots:
    void readMessage();

signals:
    void messageReceive(QJsonObject jsonObject) override;

private:
    QString ip;
    quint16 port;
    QTcpSocket tcpSocket;
};

#endif // NETWORKMANAGERIMPL_H
