#ifndef MYCALCSCREEN_H
#define MYCALCSCREEN_H

#include <QMainWindow>
#include <QTcpSocket>
#include <utility>
#include <vector>

#include "ui_calcwindow.h"

using namespace std;

class MyCalcWindow : public QMainWindow, private Ui::CalcWindow{
    Q_OBJECT

public:
    MyCalcWindow(QWidget *parent = nullptr);

public slots:
    void on_execButton_clicked(void);
    void on_radioButtonSoma_clicked(void);
    void on_radioButtonSub_clicked(void);
    void on_radioButtonMult_clicked(void);
    void on_radioButtonDiv_clicked(void);
    void on_actionByUser_triggered(void);
    void on_actionAllUsers_triggered(void);
    void onUserLogin(QString username, QString ip, int port);
    void onQuit(void);
    void readMessage(void);
    void showPieChart(QString title, vector<pair<QString, int>> operations);

private:
    QString username;
    QString ip;
    int port;
    QTcpSocket tcpSocket;
};

#endif // MYCALCEXAMPLE_H
