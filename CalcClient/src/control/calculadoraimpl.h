/*!
 * \file networkmanagerimpl.h
 * Arquivo contendo a Declaração da Classe NetworkManagerImpl
 */

#ifndef NETWORKMANAGERIMPL_H
#define NETWORKMANAGERIMPL_H

#include "calculadora.h"

#include <QTcpSocket>

/*!
 * \class NetworkManagerImpl
 * \brief Implementação da Interface NetworkManager
 */
class CalculadoraImpl : public QObject, public Calculadora{
    Q_OBJECT
public:
    CalculadoraImpl();
    virtual ~CalculadoraImpl();
    virtual void configure(QString ip, quint16 port) override;
    virtual void login(BasicUser *basicUser) override;
    virtual void doOperation(BasicUser *basicUser, double factor1, double factor2, int opCode) override;
    virtual void reportByUser(BasicUser *basicUser) override;
    virtual void reportAllUsers(AdminUser *adminUser) override;
    virtual QObject* getQObject() override;

public slots:
    /*!
     * \brief Slot para encaminhamento das mensagens recebidas pelo servidor
     */
    void readMessage();

signals:
    /*!
     * \brief Conversão do método da super classe em um signal
     * \param jsonObject Resposta recebida do servidor
     */
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
