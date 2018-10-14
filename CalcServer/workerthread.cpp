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

WorkerThread::~WorkerThread(){
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
    qDebug() << "============= Msg Recebida =============";
    qDebug() << "Msg Receive: " << message;
#endif

    QJsonDocument jsonDocument = QJsonDocument::fromJson(message.toUtf8());
    QJsonObject jsonObject = jsonDocument.object();

#ifdef DEBUG
    qDebug() << "Operation Type: " << jsonObject.value("operationType").toInt();
    qDebug() << "========================================";
#endif
    int operationType = jsonObject.value("operationType").toInt();

    switch(operationType){
    case 1:
    {
        QString username = jsonObject.value("username").toString();
        QString password = jsonObject.value("password").toString();

#ifdef DEBUG
        qDebug() << "=============== Database ===============";
        qDebug() << "Username: " << username;
        qDebug() << "Password: " << password;
#endif

        QJsonObject answerResult;
        vector<pair<QString, QString> > users = databaseHelper->getAllUsers();
        for (vector<pair<QString, QString> >::iterator it = users.begin(); it != users.end(); ++it){
            QString usernameDB = (*it).first;
            QString passwordDB = (*it).second;

#ifdef DEBUG
            qDebug() << "UsernameDB: " << usernameDB;
            qDebug() << "PasswordDB: " << passwordDB;
            qDebug() << "----------------------------------------";
#endif

            // Validar as Credenciais
            if((usernameDB == username) && (passwordDB == password)){
                // Usuário valido
                bool adminLevel = databaseHelper->isAdmin(username);
                answerResult.insert("valid", true);
                answerResult.insert("adminLevel", adminLevel);

                QJsonDocument answerDocument(answerResult);
                QString answerString(answerDocument.toJson(QJsonDocument::Compact));
                QByteArray answerData = answerString.toUtf8();

#ifdef DEBUG
                qDebug() << "============= Msg Resposta =============";
                qDebug() << "Msg Login: " << answerData;
                qDebug() << "========================================";
#endif

                tcpSocket.write(answerData);
                tcpSocket.disconnectFromHost();
                tcpSocket.waitForDisconnected();
                return;
            }
        }
        // Usuário invalido
        answerResult.insert("valid", false);

        QJsonDocument answerDocument(answerResult);
        QString answerString(answerDocument.toJson(QJsonDocument::Compact));
        QByteArray answerData = answerString.toUtf8();

#ifdef DEBUG
        qDebug() << "============= Msg Resposta =============";
        qDebug() << "Msg Resposta: " << answerData;
        qDebug() << "========================================";
#endif

        tcpSocket.write(answerData);
        tcpSocket.disconnectFromHost();
        tcpSocket.waitForDisconnected();
        break;
    }
    case 2:
    {
        QString username = jsonObject.value("username").toString();
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

        QJsonObject answerJson;
        answerJson.insert("answerType", 1);
        answerJson.insert("result", result);

        QJsonDocument answerDocument(answerJson);
        QString answerString(answerDocument.toJson(QJsonDocument::Compact));

        int userId = databaseHelper->getUserId(username);

#ifdef DEBUG
        qDebug() << "========== Dados da Resposta ===========" << endl;
        qDebug() << "userId: " << userId;
        qDebug() << "v1: " << v1;
        qDebug() << "Operação: " << operacao;
        qDebug() << "v2: " << v2;
        qDebug() << "Resultado: " << result;
        qDebug() << "========================================";
#endif

        bool exec = databaseHelper->insertOperation(userId, v1, operacao, v2, result);

#ifdef DEBUG
        qDebug() << "A query foi executada: " << exec;
#endif

        QByteArray answerData = answerString.toUtf8();

#ifdef DEBUG
        qDebug() << "============= Msg Resposta =============";
        qDebug() << "Msg Resposta: " << answerData;
        qDebug() << "========================================";
#endif

        tcpSocket.write(answerData);
        tcpSocket.disconnectFromHost();
        tcpSocket.waitForDisconnected();
        break;
    }
    case 3:
    {
        QString username = jsonObject.value("username").toString();
        vector<pair<QString, int>> operations = databaseHelper->getOperationsByUser(username);

#ifdef DEBUG
        qDebug() << "========= Operações Armazenada =========";
        for(vector<pair<QString, int>>::iterator it = operations.begin(); it!= operations.end(); ++it){
            qDebug() << "Operação: "<< (*it).first <<", Qtd: "<<(*it).second;
        }
        qDebug() << "========================================";
#endif


        QJsonObject answerJson;
        answerJson.insert("answerType", 3);

        for(vector<pair<QString, int>>::iterator it = operations.begin(); it!= operations.end(); ++it){
            answerJson.insert((*it).first, (*it).second);
        }

        QJsonDocument answerDocument(answerJson);
        QString answerString(answerDocument.toJson(QJsonDocument::Compact));
        QByteArray answerData = answerString.toUtf8();

#ifdef DEBUG
        qDebug() << "============= Msg Resposta =============";
        qDebug() << "Msg Resposta: " << answerData;
        qDebug() << "========================================";
#endif

        tcpSocket.write(answerData);
        tcpSocket.disconnectFromHost();
        tcpSocket.waitForDisconnected();

    }
        break;
    case 4:
    {
        QString username = jsonObject.value("username").toString();
        if(!databaseHelper->isAdmin(username)){
            QJsonObject answerJson;
            answerJson.insert("answerType", 4);
            QJsonDocument answerDocument(answerJson);
            QString answerString(answerDocument.toJson(QJsonDocument::Compact));
            QByteArray answerData = answerString.toUtf8();

#ifdef DEBUG
            qDebug() << "============= Msg Resposta =============";
            qDebug() << "Msg Resposta: " << answerData;
            qDebug() << "========================================";
#endif

            tcpSocket.write(answerData);
            tcpSocket.disconnectFromHost();
            tcpSocket.waitForDisconnected();

            return;
        }
        vector<pair<QString, int>> operations = databaseHelper->getAllOperations();

#ifdef DEBUG
        qDebug() << "========= Operações Armazenada =========";
        for(vector<pair<QString, int>>::iterator it = operations.begin(); it!= operations.end(); ++it){
            qDebug() << "Operação: "<< (*it).first <<", Qtd: "<<(*it).second;
        }
        qDebug() << "========================================";
#endif


        QJsonObject answerJson;
        answerJson.insert("answerType", 3);

        for(vector<pair<QString, int>>::iterator it = operations.begin(); it!= operations.end(); ++it){
            answerJson.insert((*it).first, (*it).second);
        }

        QJsonDocument answerDocument(answerJson);
        QString answerString(answerDocument.toJson(QJsonDocument::Compact));
        QByteArray answerData = answerString.toUtf8();

#ifdef DEBUG
        qDebug() << "============= Msg Resposta =============";
        qDebug() << "Msg Resposta: " << answerString;
        qDebug() << "========================================";
#endif

        tcpSocket.write(answerData);
        tcpSocket.disconnectFromHost();
        tcpSocket.waitForDisconnected();
    }
        break;
    }
}
