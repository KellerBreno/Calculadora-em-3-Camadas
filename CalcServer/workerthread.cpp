#define DEBUG

#include "workerthread.h"

#include <QtNetwork>
#include <QDebug>
#include <QDataStream>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QJsonObject>
#include <QJsonDocument>

WorkerThread::WorkerThread(int socketDescriptor, QObject *parent, DatabaseHelper *databaseHelper)
    : QThread(parent), socketDescriptor(socketDescriptor), databaseHelper(databaseHelper){
}

void WorkerThread::run(){
    QTcpSocket tcpSocket;
    if (!tcpSocket.setSocketDescriptor(socketDescriptor)) {
        emit error(tcpSocket.error());
        return;
    }

    // Realizar Input de Message
    tcpSocket.waitForReadyRead(-1);

    QByteArray data = tcpSocket.readLine();
    QString message = QString::fromStdString(data.toStdString());

#ifdef DEBUG
    qDebug() << "Msg: " << message;
#endif

    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    QJsonObject jsonObject = doc.object();

#ifdef DEBUG
    qDebug() << "Operation Type: " << jsonObject.value("operationType").toInt();
#endif
    int operationType = jsonObject.value("operationType").toInt();

    switch(operationType){
    case 1:
    {
        QString username = jsonObject.value("username").toString();
        QString password = jsonObject.value("password").toString();

#ifdef DEBUG
        qDebug() << "Username: " << username;
        qDebug() << "Password: " << password;
#endif

        QJsonObject loginResult;
        vector<pair<QString, QString> > users = databaseHelper->getUsers();
        for (vector<pair<QString, QString> >::iterator it = users.begin(); it != users.end(); ++it){
            QString usernameDB = (*it).first;
            QString passwordDB = (*it).second;

#ifdef DEBUG
            qDebug() << "UsernameDB: " << usernameDB;
            qDebug() << "PasswordDB: " << passwordDB;
#endif

            // Validar as Credenciais
            if((usernameDB == username) && (passwordDB == password)){
                // Usuário valido
                loginResult.insert("valid", true);

                QJsonDocument loginDocument(loginResult);
                QString responseData(loginDocument.toJson(QJsonDocument::Compact));
                QByteArray msgLogin = responseData.toUtf8();

#ifdef DEBUG
                qDebug() << "Msg Login: " << msgLogin;
#endif

                tcpSocket.write(msgLogin);
                tcpSocket.disconnectFromHost();
                tcpSocket.waitForDisconnected();
                return;
            }
        }
        // Usuário invalido
        loginResult.insert("valid", false);

        QJsonDocument loginDocument(loginResult);
        QString responseData(loginDocument.toJson(QJsonDocument::Compact));
        QByteArray msgLogin = responseData.toUtf8();

#ifdef DEBUG
        qDebug() << "Msg Login: " << msgLogin;
#endif

        tcpSocket.write(msgLogin);
        tcpSocket.disconnectFromHost();
        tcpSocket.waitForDisconnected();
        break;
    }
    case 2:
    {
        QString usernameInsert = jsonObject.value("username").toString();
        int opCode = jsonObject.value("opCode").toInt();
        double v1 = jsonObject.value("v1").toDouble();
        double v2 = jsonObject.value("v2").toDouble();
        double result;
        QString operacao;

        switch(opCode){
        case 1: // Adição
            result = v1 + v2;
            operacao = "Adição";
            break;
        case 2: // Subtração
            result = v1 - v2;
            operacao = "Subtração";
            break;
        case 3: // Multiplicação
            result = v1 * v2;
            operacao = "Multiplicação";
            break;
        case 4: // Divisão
            result = v1 / v2;
            operacao = "Divisão";
            break;
        }

        QJsonObject response;
        response.insert("responseType", 1);
        response.insert("result", result);

        QJsonDocument resultDoc(response);
        QString resultData(resultDoc.toJson(QJsonDocument::Compact));


        int userId = databaseHelper->getUserId(usernameInsert);

#ifdef DEBUG
        qDebug() << "===========================================" << endl;
        qDebug() << "userId: " << userId;
        qDebug() << "v1: " << v1;
        qDebug() << "Operação: " << operacao;
        qDebug() << "v2: " << v2;
        qDebug() << "Resultado: " << result;
        qDebug() << "===========================================" << endl;
#endif

        bool exec = databaseHelper->insertOperation(userId, v1, operacao, v2, result);

#ifdef DEBUG
        qDebug() << "executou :" << exec;
#endif

        QByteArray msgLogin = resultData.toUtf8();

#ifdef DEBUG
        qDebug() << "Msg Login: " << msgLogin;
#endif

        tcpSocket.write(msgLogin);
        tcpSocket.disconnectFromHost();
        tcpSocket.waitForDisconnected();
        break;
    }
    case 3:
    {
        QString username = jsonObject.value("username").toString();
        vector<pair<QString, int>> operations = databaseHelper->getOperationsByUser(username);

#ifdef DEBUG
        qDebug() << "===========================================" << endl;
        for(vector<pair<QString, int>>::iterator it = operations.begin(); it!= operations.end(); ++it){
            qDebug() << "Operação: "<< (*it).first <<", Qtd: "<<(*it).second;
        }
        qDebug() << "===========================================" << endl;
#endif


        QJsonObject response;
        response.insert("responseType", 3);

        for(vector<pair<QString, int>>::iterator it = operations.begin(); it!= operations.end(); ++it){
            response.insert((*it).first, (*it).second);
        }

        QJsonDocument resultDoc(response);
        QString resultData(resultDoc.toJson(QJsonDocument::Compact));
        QByteArray msgLogin = resultData.toUtf8();

#ifdef DEBUG
        qDebug() << "Msg Login: " << msgLogin;
#endif

        tcpSocket.write(msgLogin);
        tcpSocket.disconnectFromHost();
        tcpSocket.waitForDisconnected();

    }
        break;
    case 4:
    {
        vector<pair<QString, int>> operations = databaseHelper->getOperations();

#ifdef DEBUG
        qDebug() << "===========================================" << endl;
        for(vector<pair<QString, int>>::iterator it = operations.begin(); it!= operations.end(); ++it){
            qDebug() << "Operação: "<< (*it).first <<", Qtd: "<<(*it).second;
        }
        qDebug() << "===========================================" << endl;
#endif


        QJsonObject response;
        response.insert("responseType", 3);

        for(vector<pair<QString, int>>::iterator it = operations.begin(); it!= operations.end(); ++it){
            response.insert((*it).first, (*it).second);
        }

        QJsonDocument resultDoc(response);
        QString resultData(resultDoc.toJson(QJsonDocument::Compact));
        QByteArray msgLogin = resultData.toUtf8();

#ifdef DEBUG
        qDebug() << "Msg Login: " << msgLogin;
#endif

        tcpSocket.write(msgLogin);
        tcpSocket.disconnectFromHost();
        tcpSocket.waitForDisconnected();
    }
        break;
    }
}
