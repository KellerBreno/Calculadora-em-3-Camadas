#include "gui/mycalcwindow.h"
#include "gui/mylogindialog.h"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    MyCalcWindow calcWindow;
    calcWindow.setEnabled(false);
    MyLoginDialog loginDialog;

    QObject::connect(&loginDialog, SIGNAL(logged(User*)), &calcWindow, SLOT(onUserLogin(User*)));
    QObject::connect(&loginDialog, SIGNAL(quit(void)), &calcWindow, SLOT(onQuit(void)));

    calcWindow.show();
    loginDialog.show();

    return app.exec();
}
