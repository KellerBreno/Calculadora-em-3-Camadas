#include <QApplication>
#include <QtCore>

#include <stdlib.h>

#include "serverdialogimpl.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ServerDialog *serverDialog = new ServerDialogImpl();
    serverDialog->show();

    app.exec();

    delete serverDialog;
    return 0;
}
