#include "../mycalcwindow.h"
#include "ui_calcwindow.h"

#include <QWidget>
#include <QMessageBox>
#include <QDialog>
#include <QDebug>
#include <QtTest/QtTest>
#include <QPushButton>
#include <QRadioButton>

class MyCalcWindowTest : public QObject
{
    Q_OBJECT

public:
    MyCalcWindowTest();
    ~MyCalcWindowTest();

private slots:
    void verificaRadioButtons();

    void casoDeUsoAlternativo_data();
    void casoDeUsoAlternativo();

    void casoUsoPrincipal_data();
    void casoUsoPrincipal();

private:
    void setupMain(QString username, bool adminLevel, QString ip, int port);

    MyCalcWindow calc;
};
