/*!
 * \file serverdialog.h
 * Arquivo contendo a declaração da Interface ServerDialog.
 */

#ifndef SERVERDIALOG_H
#define SERVERDIALOG_H

#include <QWidget>

/*!
 * \class ServerDialog
 * \brief Classe para exibição dos dados do servidor.
 *
 */
class ServerDialog{
public:
    /*!
     * \brief Método que exibe um janela de dialogo com as informações do server.
     * \sa Server.
     */
    virtual void show() = 0;
};

#endif // SERVERDIALOG_H
