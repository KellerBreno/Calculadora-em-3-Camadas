#define DEBUG

#include "networkmanagerimpl.h"
#include <QJsonDocument>

NetworkManager* NetworkManager::instance =nullptr;

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

void NetworkManagerImpl::login(QString username, QString password){
    if(ip.isEmpty() || port == 0){
        // Throw expection
        return;
    }

    tcpSocket.connectToHost(ip, port);

    QJsonObject jsonObject;
    jsonObject.insert("operationType", 1);
    jsonObject.insert("username", username);
    jsonObject.insert("password", password);

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

void NetworkManagerImpl::doOperation(QString username, double factor1, double factor2, int opCode){
    if(ip.isEmpty() || port == 0){
        // Throw expection
        return;
    }

    tcpSocket.connectToHost(ip, port);

    QJsonObject jsonObject;
    jsonObject.insert("operationType", 2);
    jsonObject.insert("username", username);
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

void NetworkManagerImpl::reportByUser(QString username){
    if(ip.isEmpty() || port == 0){
        // Throw expection
        return;
    }

    tcpSocket.connectToHost(ip, port);

    QJsonObject jsonObject;
    jsonObject.insert("operationType", 3);
    jsonObject.insert("username", username);

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

void NetworkManagerImpl::reportAllUsers(QString username){
    if(ip.isEmpty() || port == 0){
        // Throw expection
        return;
    }

    tcpSocket.connectToHost(ip, port);

    QJsonObject jsonObject;
    jsonObject.insert("operationType", 4);
    jsonObject.insert("username", username);

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
