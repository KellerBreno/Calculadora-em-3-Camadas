#ifndef DIALOG_H
#define DIALOG_H

#include <QWidget>
#include "server.h"

class QLabel;
class QPushButton;

class Dialog : public QWidget{
    Q_OBJECT

    friend class DialogTest;
    friend class SocketsTest;

public:
    Dialog(QWidget *parent = 0);

private:
    QLabel *statusLabel;
    QPushButton *quitButton;
    Server server;
};

#endif // DIALOG_H
