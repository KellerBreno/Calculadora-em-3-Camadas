#include "../mylogindialog.h"
#include "ui_logindialog.h"

#include "../mycalcwindow.h"
#include "ui_calcwindow.h"

#include <QWidget>
#include <QMessageBox>
#include <QDialog>
#include <QDebug>
#include <QtTest/QtTest>

class MyLoginDialogTest : public QObject
{
    Q_OBJECT

public:
    MyLoginDialogTest();
    ~MyLoginDialogTest();

private slots:
    void casoUsoSanidade();

    void casoDeUsoAlternativo_data();
    void casoDeUsoAlternativo();

    void casoUsoPrincipal_data();
    void casoUsoPrincipal();

    void timeOut();

private:
    void setupMain();
    void clearInputs();

    void verificaCamposCalcWindow(bool active);
    void verificaQActionCalcWindow(bool active, bool isAdm);

    MyLoginDialog d;
    MyCalcWindow calc;

    QString msgResult;
};
