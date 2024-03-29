/*!
 * \file mylogindialog.h
 * Arquivo contendo a declaração da Classe MyLoginDialog.
 */

#ifndef MYLOGINDIALOG_H
#define MYLOGINDIALOG_H

#include <QWidget>
#include <QTcpSocket>
#include <QJsonObject>

#include <data/user.h>

#include "ui_logindialog.h"

/*!
 * \class MyLoginDialog
 * \brief Classe para gerenciar as requisições de login.
 *
 * Esta classe gerencia as iterações do usuário com uma janela de login e realiza a validação dos dados em um servidor.
 *
 */
class MyLoginDialog : public QWidget, private Ui::LoginDialog {
    Q_OBJECT

    /*!
     * \brief Classe para Testes de MyLoginDialog.
     */
    friend class MyLoginDialogTest;

public:
    MyLoginDialog(QWidget *parent = nullptr);

public slots:
    void on_login_button_clicked(void);
    void on_cancel_button_clicked(void);
    void readMessage(QJsonObject jsonObject);

signals:
    /*!
     * \brief Signal emitido quando a operação de login é realizada com sucesso.
     * \param user Referencia ao usuário da aplicação.
     */
    void logged(User *user);

    /*!
     * \brief Signal emitido para finalizar a aplicação.
     */
    void quit(void);

private:
    /*!
     * \brief TCPSocket utilizado pela aplicação para comunicar com servidor.
     */
    QTcpSocket tcpSocket;

    /*!
     * \brief Referencia ao usuário da aplicação
     */
    User *user;
};

#endif // MYLOGINDIALOG_H
