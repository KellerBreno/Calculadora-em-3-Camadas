#ifndef MYCALCSCREEN_H
#define MYCALCSCREEN_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

#include <utility>
#include <vector>

#include "ui_calcwindow.h"

QT_CHARTS_USE_NAMESPACE

using namespace std;

class MyCalcWindow : public QMainWindow, private Ui::CalcWindow{
    Q_OBJECT

    friend class MyLoginDialogTest;
    friend class MyCalcWindowTest;

public:
    MyCalcWindow(QWidget *parent = nullptr);
    virtual ~MyCalcWindow();

public slots:
    void on_execButton_clicked(void);
    void on_radioButtonSoma_clicked(void);
    void on_radioButtonSub_clicked(void);
    void on_radioButtonMult_clicked(void);
    void on_radioButtonDiv_clicked(void);
    void on_actionByUser_triggered(void);
    void on_actionAllUsers_triggered(void);
    void onUserLogin(QString username, bool adminLevel, QString ip, int port);
    void onQuit(void);
    void readMessage(void);
    void showPieChart(QString title, vector<pair<QString, int>> operations);

private:
    void execute(void);
    QString username;
    QString ip;
    int port;
    QTcpSocket tcpSocket;
    bool adminLevel;
    QMainWindow* chartWindow;
};

#endif // MYCALCEXAMPLE_H
