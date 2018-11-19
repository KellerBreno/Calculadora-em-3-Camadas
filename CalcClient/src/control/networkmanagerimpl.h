/*!
 * \file networkmanagerimpl.h
 * Arquivo contendo a Declaração da Classe NetworkManagerImpl
 */

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
    virtual void login(BasicUser *basicUser) override;
    virtual void doOperation(BasicUser *basicUser, double factor1, double factor2, int opCode) override;
    virtual void reportByUser(BasicUser *basicUser) override;
    virtual void reportAllUsers(AdminUser *adminUser) override;
    virtual QObject* getQObject() override;

public slots:
    void readMessage();

signals:
    void messageReceive(QJsonObject jsonObject) override;

private:
    /*!
     * \brief IP do servidor
     */
    QString ip;

    /*!
     * \brief Porta do servidor
     */
    quint16 port;

    /*!
     * \brief Socket TCP utilizado para conexões
     */
    QTcpSocket tcpSocket;
};

#endif // NETWORKMANAGERIMPL_H
