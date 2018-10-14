#include "mycalcwindow.h"
#include "mylogindialog.h"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    MyCalcWindow calcWindow;
    calcWindow.setEnabled(false);
    MyLoginDialog loginDialog;

    QObject::connect(&loginDialog, SIGNAL(logged(QString, bool, QString, int)), &calcWindow, SLOT(onUserLogin(QString, bool, QString, int)));
    QObject::connect(&loginDialog, SIGNAL(quit(void)), &calcWindow, SLOT(onQuit(void)));

    calcWindow.show();
    loginDialog.show();

    return app.exec();
}
