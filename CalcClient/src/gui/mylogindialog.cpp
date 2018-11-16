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
#include <QJsonDocument>

#include <iostream>

#include <control/networkmanagerimpl.h>

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

    NetworkManager *networkManager = NetworkManager::getInstance();
    networkManager->configure(ip,port.toInt());
    connect(networkManager->getQObject(), SIGNAL(messageReceive(QJsonObject)), this, SLOT(readMessage(QJsonObject)));
    networkManager->login(username,password);
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
void MyLoginDialog::readMessage(QJsonObject jsonObject){
    int answerType = jsonObject.value("answerType").toInt();
    if(answerType!=0){
        QMessageBox::critical(this, "Login", "Ocorreu um erro, por favor tente novamente", QMessageBox::Ok);
        return;
    }

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
        disconnect(NetworkManager::getInstance()->getQObject(), SIGNAL(messageReceive(QJsonObject)), this, SLOT(readMessage(QJsonObject)));
        emit logged(username, adminLevel);
        close();
    } else {
        QMessageBox::information(this, "Login", "Credenciais Incorretas", QMessageBox::Ok);
    }
}
