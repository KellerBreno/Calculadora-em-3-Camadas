#define DEBUG

#include "mycalcwindow.h"
#include "ui_calcwindow.h"

#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include <QJsonObject>
#include <QJsonDocument>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

#include <string>
#include <sstream>
#include <iostream>

QT_CHARTS_USE_NAMESPACE

// TODO override X action
MyCalcWindow::MyCalcWindow(QWidget *parent) : QMainWindow (parent){
    setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    connect(&tcpSocket, &QIODevice::readyRead, this, &MyCalcWindow::readMessage);
}

void MyCalcWindow::on_execButton_clicked(void){
    double parcela1 = input1->value();
    double parcela2 = input2->value();

    int opCode;
    if(radioButtonSoma->isChecked()){
        opCode = 1;
    } else if(radioButtonSub->isChecked()){
        opCode = 2;
    } else if(radioButtonMult->isChecked()){
        opCode = 3;
    } else if(radioButtonDiv->isChecked()){
        opCode = 4;
    }

    tcpSocket.connectToHost(ip, port);

    QJsonObject jsonObject;
    jsonObject.insert("operationType", 2);
    jsonObject.insert("username", username);
    jsonObject.insert("v1", parcela1);
    jsonObject.insert("opCode", opCode);
    jsonObject.insert("v2", parcela2);

    QJsonDocument jsonDocument(jsonObject);
    QString data(jsonDocument.toJson(QJsonDocument::Compact));

    QByteArray msg = data.toUtf8();

#ifdef DEBUG
    qDebug() << "Msg: " << msg;
#endif

    tcpSocket.write(msg);
}

void MyCalcWindow::on_radioButtonSoma_clicked(void){
    on_execButton_clicked();
}

void MyCalcWindow::on_radioButtonSub_clicked(void){
    on_execButton_clicked();
}

void MyCalcWindow::on_radioButtonMult_clicked(void){
    on_execButton_clicked();
}

void MyCalcWindow::on_radioButtonDiv_clicked(void){
    on_execButton_clicked();
}

void MyCalcWindow::onUserLogin(QString username, bool adminLevel, QString ip, int port){
    setEnabled(true);
    this->username = username;
    this->ip = ip;
    this->port = port;
    this->adminLevel = adminLevel;
    actionAllUsers->setVisible(adminLevel);
}

void MyCalcWindow::onQuit(void){
    close();
}

void MyCalcWindow::readMessage(){
    tcpSocket.waitForReadyRead(-1);

    QByteArray data = tcpSocket.readLine();
    QString message = QString::fromStdString(data.toStdString());

#ifdef DEBUG
    qDebug() << "Msg: " << message;
#endif

    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    QJsonObject jsonObject = doc.object();

    int responseType = jsonObject.value("responseType").toInt();
    switch (responseType) {
    case 1:
    {
        double result = jsonObject.value("result").toDouble();

#ifdef DEBUG
        qDebug() << "Result: " << result;
#endif

        // Tratar Resultado

        QString resultStr;
        resultStr.setNum(result);
        textEditResult->setText(resultStr);
    }
        break;
    case 2:
    {
        vector<pair<QString, int>> operations;

        operations.push_back(make_pair("Adição", jsonObject.value("Adição").toInt()));
        operations.push_back(make_pair("Subtração", jsonObject.value("Subtração").toInt()));
        operations.push_back(make_pair("Multiplicação", jsonObject.value("Multiplicação").toInt()));
        operations.push_back(make_pair("Divisão", jsonObject.value("Divisão").toInt()));

        showPieChart("Operações feitas pelo Usuário: " + username, operations);
    }
        break;
    case 3:
    {
        vector<pair<QString, int>> operations;

        operations.push_back(make_pair("Adição", jsonObject.value("Adição").toInt()));
        operations.push_back(make_pair("Subtração", jsonObject.value("Subtração").toInt()));
        operations.push_back(make_pair("Multiplicação", jsonObject.value("Multiplicação").toInt()));
        operations.push_back(make_pair("Divisão", jsonObject.value("Divisão").toInt()));

        showPieChart("Operações feitas por Todos Usuários", operations);
    }
        break;
    case 4:
    {
        QMessageBox::information(this, "CalcWindow", "O seu usuário não tem permissão para realizar essa ação", QMessageBox::Ok);
    }
        break;
    }

}

void MyCalcWindow::on_actionByUser_triggered(void){
    tcpSocket.connectToHost(ip, port);

    QJsonObject jsonObject;
    jsonObject.insert("operationType", 3);
    jsonObject.insert("username", username);

    QJsonDocument jsonDocument(jsonObject);
    QString data(jsonDocument.toJson(QJsonDocument::Compact));

    QByteArray msg = data.toUtf8();

#ifdef DEBUG
    qDebug() << "Msg: " << msg;
#endif

    tcpSocket.write(msg);
}

void MyCalcWindow::on_actionAllUsers_triggered(void){
    if(!adminLevel){
        return;
    }
    tcpSocket.connectToHost(ip, port);

    QJsonObject jsonObject;
    jsonObject.insert("operationType", 4);
    jsonObject.insert("username", username);

    QJsonDocument jsonDocument(jsonObject);
    QString data(jsonDocument.toJson(QJsonDocument::Compact));

    QByteArray msg = data.toUtf8();

#ifdef DEBUG
    qDebug() << "Msg: " << msg;
#endif

    tcpSocket.write(msg);
}

void MyCalcWindow::showPieChart(QString title, vector<pair<QString, int>> operations){
    QPieSeries *series = new QPieSeries();

    for(vector<pair<QString, int>>::iterator it = operations.begin(); it != operations.end(); ++it){
        series->append((*it).first, (*it).second);
    }

//    QPieSlice *sliceAdd = series->slices().at(0);
//    sliceAdd->setLabelVisible();
//    QPieSlice *sliceSub = series->slices().at(1);
//    sliceSub->setLabelVisible();
//    QPieSlice *sliceMult = series->slices().at(2);
//    sliceMult ->setLabelVisible();
//    QPieSlice *sliceDiv = series->slices().at(3);
//    sliceDiv->setLabelVisible();

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(title);
    //chart->legend()->hide();

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QMainWindow *window = new QMainWindow();
    window->setCentralWidget(chartView);
    window->resize(400, 300);
    window->show();
    // TODO leak de memoria
}

