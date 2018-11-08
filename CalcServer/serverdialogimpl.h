/*!
 * \file serverdialogimpl.h
 * Arquivo contendo a declaração da Classe ServerDialogImpl.
 */

#ifndef SERVERDIALOGIMPL_H
#define SERVERDIALOGIMPL_H

#include "server.h"
#include "serverdialog.h"

class QLabel;
class QPushButton;

/*!
 * \class ServerDialogImpl
 * \brief Implementação da interface ServerDialog.
 *
 * Esta classe cria uma instância de Server e exibe suas informações.
 *
 */
class ServerDialogImpl : public QWidget, public ServerDialog{
    Q_OBJECT

    /*!
     * \brief Classe de Testes para ServerDialog
     */
    friend class DialogTest;

    /*!
     * \brief Classe de Testes para Sockets
     */
    friend class SocketsTest;

public:
    ServerDialogImpl(QWidget *parent = nullptr);
    virtual ~ServerDialogImpl();
    virtual void show();

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
    Server *server;

    /*!
     * \brief Construtor de Cópia.
     * \param rhs Objeto a ser copiado.
     */
    ServerDialogImpl(const ServerDialogImpl& rhs);

    /*!
     * \brief Sobrecarga do operador =.
     * \param rhs Objeto a ser copiado.
     * \return Novo objeto copiado.
     */
    ServerDialogImpl& operator=(const ServerDialogImpl& rhs);

};

#endif // SERVERDIALOGIMPL_H
