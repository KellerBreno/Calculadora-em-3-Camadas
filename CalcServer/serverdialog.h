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
    virtual void show() = 0;
};

#endif // SERVERDIALOG_H
