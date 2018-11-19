/*!
 * \file networkmanagerimpl.cpp
 * Arquivo contendo a Implementação da Classe NetworkManagerImpl
 */

#define DEBUG

#include "networkmanagerimpl.h"
#include <QJsonDocument>

NetworkManager* NetworkManager::instance = nullptr;

NetworkManager* NetworkManager::getInstance(){
    if(instance == nullptr){
        instance = new NetworkManagerImpl();
    }
    return instance;
}

NetworkManagerImpl::NetworkManagerImpl(){
    ip = "";
    port = 0;
    QObject::connect(&tcpSocket, &QIODevice::readyRead, this, &NetworkManagerImpl::readMessage);
}

NetworkManagerImpl::~NetworkManagerImpl(){

}

void NetworkManagerImpl::configure(QString ip, quint16 port){
    this->ip = ip;
    this->port = port;
}

void NetworkManagerImpl::login(BasicUser *basicUser){
    if(ip.isEmpty() || port == 0){
        // Throw expection
        return;
    }

    if(basicUser == nullptr){
        // Throw exception
        return;
    }

    tcpSocket.connectToHost(ip, port);

    QJsonObject jsonObject;
    jsonObject.insert("operationType", 1);
    jsonObject.insert("username", basicUser->getUsername());
    jsonObject.insert("password", basicUser->getPassword());

    QJsonDocument jsonDocument(jsonObject);
    QString jsonString(jsonDocument.toJson(QJsonDocument::Compact));
    QByteArray jsonData = jsonString.toUtf8();

#ifdef DEBUG
    qDebug() << "=========== Mensagem Enviada ===========";
    qDebug() << "Msg: " << jsonData;
    qDebug() << "========================================";
#endif

    tcpSocket.write(jsonData);
}

void NetworkManagerImpl::doOperation(BasicUser *basicUser, double factor1, double factor2, int opCode){
    if(ip.isEmpty() || port == 0){
        // Throw expection
        return;
    }

    if(basicUser==nullptr){
        // Throw exception
        return;
    }

    tcpSocket.connectToHost(ip, port);

    QJsonObject jsonObject;
    jsonObject.insert("operationType", 2);
    jsonObject.insert("username", basicUser->getUsername());
    jsonObject.insert("v1", factor1);
    jsonObject.insert("opCode", opCode);
    jsonObject.insert("v2", factor2);

    QJsonDocument jsonDocument(jsonObject);
    QString jsonString(jsonDocument.toJson(QJsonDocument::Compact));

    QByteArray jsonData = jsonString.toUtf8();

 #ifdef DEBUG
    qDebug() << "=========== Mensagem Enviada ===========";
    qDebug() << "Msg: " << jsonData;
    qDebug() << "========================================";
 #endif

    tcpSocket.write(jsonData);
}

void NetworkManagerImpl::reportByUser(BasicUser *basicUser){
    if(ip.isEmpty() || port == 0){
        // Throw expection
        return;
    }

    if(basicUser==nullptr){
        // Throw exception
        return;
    }

    tcpSocket.connectToHost(ip, port);

    QJsonObject jsonObject;
    jsonObject.insert("operationType", 3);
    jsonObject.insert("username", basicUser->getUsername());

    QJsonDocument jsonDocument(jsonObject);
    QString jsonString(jsonDocument.toJson(QJsonDocument::Compact));

    QByteArray jsonData = jsonString.toUtf8();

 #ifdef DEBUG
    qDebug() << "=========== Mensagem Enviada ===========";
    qDebug() << "Msg: " << jsonData;
    qDebug() << "========================================";
 #endif

    tcpSocket.write(jsonData);
}

void NetworkManagerImpl::reportAllUsers(AdminUser *adminUser){
    if(ip.isEmpty() || port == 0){
        // Throw expection
        return;
    }

    if(adminUser==nullptr){
        // Throw exception
        return;
    }


    tcpSocket.connectToHost(ip, port);

    QJsonObject jsonObject;
    jsonObject.insert("operationType", 4);
    jsonObject.insert("username", adminUser->getUsername());

    QJsonDocument jsonDocument(jsonObject);
    QString jsonString(jsonDocument.toJson(QJsonDocument::Compact));

    QByteArray jsonData = jsonString.toUtf8();

 #ifdef DEBUG
    qDebug() << "=========== Mensagem Enviada ===========";
    qDebug() << "Msg: " << jsonData;
    qDebug() << "========================================";
 #endif

    tcpSocket.write(jsonData);
}

void NetworkManagerImpl::readMessage(){
    tcpSocket.waitForReadyRead(-1);

    QByteArray jsonData = tcpSocket.readLine();
    QString jsonString = QString::fromStdString(jsonData.toStdString());

 #ifdef DEBUG
    qDebug() << "========== Mensagem Recebida ===========";
    qDebug() << "Msg: " << jsonString;
    qDebug() << "========================================";
 #endif

    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonObject jsonObject = jsonDocument.object();

    emit messageReceive(jsonObject);
}

QObject* NetworkManagerImpl::getQObject(){
    return this;
}
