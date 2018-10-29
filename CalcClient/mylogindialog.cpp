/*!
 * \file mylogindialog.cpp
 * Arquivo contendo a implementação da Classe MyLoginDialog.
 */

/*!
 * \def DEBUG
 * Flag demarcando se as mensagens de debug devem ou não serem exibidas.
 */
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

/*!
 * \brief Construtor Padrão para a classe MyLoginDialog.
 *
 * Inicializa o atributo parent, configura a interface por meio do método 'setupUi' da classe pai LoginDialog e
 * conecta o slot para a leitura de mensagens do servidor.
 *
 * \param parent Referência ao componente pai.
 *
 */
MyLoginDialog::MyLoginDialog(QWidget *parent) : QWidget(parent){
    setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    connect(&tcpSocket, &QIODevice::readyRead, this, &MyLoginDialog::readMessage);
}

/*!
 * \brief Slot chamado para realizar a operação de login.
 *
 * Recupera as informações da interface e realiza um requisição de autenticação ao servidor.
 *
 * \sa MyLoginDialog::readMessage().
 */
void MyLoginDialog::on_login_button_clicked(){
    // Pega dados de login do usuário por meio da interface
    QString username = user_input_line->text();
    QString password = password_input_line->text();
    QString ip = ip_input_line->text();
    QString port = port_input_line->text();

    if(username.isEmpty() || password.isEmpty() || ip.isEmpty() || port.isEmpty()){
        QMessageBox::critical(this, "Login", "Por favor preencha todos campos acima", QMessageBox::Ok);
        return;
    }

    tcpSocket.connectToHost(ip, port.toInt());

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

/*!
 * \brief Slot chamado para finalizar a aplicação.
 *
 * \sa MyLoginDialog::quit().
 */
void MyLoginDialog::on_cancel_button_clicked(){
    emit quit();
    close();
}

/*!
 * \brief Slot chamado quando o socket recebe uma mensagem de resposta do servidor.
 *
 * Esse método recebe uma resposta do servidor sobre a tentativa de login. Caso positivo emite um signal informando que o usuário foi
 * autenticado. Caso contrário mostra uma janela de erro.
 *
 * \sa MyLoginDialog::on_login_button_clicked(), MyLoginDialog::logged(QString,bool,QString,int).
 */
void MyLoginDialog::readMessage(){
    tcpSocket.waitForReadyRead(-1);

    QByteArray jsonData = tcpSocket.readLine();
    QString jsonString = QString::fromStdString(jsonData.toStdString());

#ifdef DEBUG
    qDebug() << "========== Mensagem Recebida ===========";
    qDebug() << "Msg: " << jsonString;
#endif

    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonObject jsonObject = jsonDocument.object();

    bool valid = jsonObject.value("valid").toBool();

#ifdef DEBUG
    qDebug() << "response: " << valid;
    qDebug() << "========================================";
#endif

    if(valid){
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
