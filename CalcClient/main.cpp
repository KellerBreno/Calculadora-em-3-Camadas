#include "mycalcwindow.h"
#include "mylogindialog.h"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    MyCalcWindow myCalcWindow;
    myCalcWindow.setEnabled(false);
    MyLoginDialog myLoginDialog;
    myLoginDialog.setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowStaysOnTopHint);

    QObject::connect(&myLoginDialog, SIGNAL(logged(QString, QString, int)), &myCalcWindow, SLOT(onUserLogin(QString, QString, int)));
    QObject::connect(&myLoginDialog, SIGNAL(quit(void)), &myCalcWindow, SLOT(onQuit(void)));

    myCalcWindow.show();
    myLoginDialog.show();

    return app.exec();
}
