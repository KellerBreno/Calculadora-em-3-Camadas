#ifndef MYLOGINDIALOG_H
#define MYLOGINDIALOG_H

#include <QWidget>
#include <QTcpSocket>

#include "ui_logindialog.h"

class MyLoginDialog : public QWidget, private Ui::LoginDialog {
    Q_OBJECT

public:
    MyLoginDialog(QWidget *parent = nullptr);

public slots:
    void on_login_button_clicked(void);
    void on_cancel_button_clicked(void);
    void readMessage(void);

signals:
    void logged(QString username, bool adminLevel, QString ip, int port);
    void quit(void);

private:
    QTcpSocket tcpSocket;

};

#endif // MYLOGINDIALOG_H
