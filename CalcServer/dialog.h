/*!
 * \file dialog.h
 * Arquivo contendo a declaração da Classe Dialog.
 */

#ifndef DIALOG_H
#define DIALOG_H

#include <QWidget>
#include "server.h"

class QLabel;
class QPushButton;

/*!
 * \class Dialog
 * \brief Classe para exibição dos dados do servidor.
 *
 * Esta classe cria uma instância de Server e exibe suas informações.
 *
 */
class Dialog : public QWidget{
    Q_OBJECT

    /*!
     * \brief Classe de Testes para Dialog
     */
    friend class DialogTest;

    /*!
     * \brief Classe de Testes para Sockets
     */
    friend class SocketsTest;

public:
    Dialog(QWidget *parent = 0);

private:
    /*!
     * \brief QLabel para exibição dos dados do servidor.
     */
    QLabel *statusLabel;

    /*!
     * \brief Botão de sair da aplicação
     */
    QPushButton *quitButton;

    /*!
     * \brief Instância de Server
     */
    Server server;
};

#endif // DIALOG_H
