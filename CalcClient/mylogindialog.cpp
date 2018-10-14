#define DEBUG

#include "mylogindialog.h"
#include "ui_logindialog.h"

#include <QMessageBox>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDialog>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>

#include <iostream>

using namespace std;

// TODO override X action
MyLoginDialog::MyLoginDialog(QWidget *parent) : QWidget(parent){
    setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    connect(&tcpSocket, &QIODevice::readyRead, this, &MyLoginDialog::readMessage);
}

void MyLoginDialog::on_login_button_clicked(){
    // Pega dados de login do usuário por meio da interface
    QString username = user_input_line->text();
    QString password = password_input_line->text();
    QString ip = ip_input_line->text();
    QString port = port_input_line->text();

    if(username.isEmpty() || password.isEmpty()){
        QMessageBox::critical(this, "Login", "Por favor preencha os dois campos", QMessageBox::Ok);
        return;
    }

    tcpSocket.connectToHost(ip, port.toInt());

    QJsonObject jsonObject;
    jsonObject.insert("operationType", 1);
    jsonObject.insert("username", username);
    jsonObject.insert("password", password);

    QJsonDocument jsonDocument(jsonObject);
    QString data(jsonDocument.toJson(QJsonDocument::Compact));

    QByteArray msg = data.toUtf8();

#ifdef DEBUG
    qDebug() << "Msg: " << msg;
#endif

    tcpSocket.write(msg);
}

void MyLoginDialog::on_cancel_button_clicked(){
    emit quit();
    close();
}

void MyLoginDialog::readMessage(){
    tcpSocket.waitForReadyRead(-1);

    QByteArray data = tcpSocket.readLine();
    QString message = QString::fromStdString(data.toStdString());

#ifdef DEBUG
    qDebug() << "Msg: " << message;
#endif

    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    QJsonObject jsonObject = doc.object();

    bool response = jsonObject.value("valid").toBool();
    // Tratar Resultado

#ifdef DEBUG
    qDebug() << "response: " << response;
#endif

    if(response){
        QString username = user_input_line->text();
        QString ip = ip_input_line->text();
        QString port = port_input_line->text();
        bool adminLevel = jsonObject.value("adminLevel").toBool();
        QMessageBox::information(this, "Login", "Seja Bem Vindo, " + username, QMessageBox::Ok);
        // Abre a calculadora
        emit logged(username, adminLevel, ip, port.toInt());
        close();
    } else {
        QMessageBox::information(this, "Login", "Credenciais Incorretas", QMessageBox::Ok);
    }
}
