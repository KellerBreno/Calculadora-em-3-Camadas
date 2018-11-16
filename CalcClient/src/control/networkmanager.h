#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QString>
#include <QObject>
#include <QJsonObject>

class NetworkManager{
private:
    static NetworkManager* instance;
public:
    static NetworkManager* getInstance();
    virtual void configure(QString ip, quint16 port) = 0;
    virtual void login(QString username, QString password) = 0;
    virtual void doOperation(QString username, double factor1, double factor2, int opCode) = 0;
    virtual void reportByUser(QString username) = 0;
    virtual void reportAllUsers(QString username) = 0;
    virtual QObject* getQObject() = 0;
    virtual void messageReceive(QJsonObject jsonObject) = 0;
};

#endif // NETWORKMANAGER_H
