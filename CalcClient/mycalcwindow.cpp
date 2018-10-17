#define DEBUG

#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include <QJsonObject>
#include <QJsonDocument>

#include <string>
#include <sstream>
#include <iostream>

#include "mycalcwindow.h"
#include "ui_calcwindow.h"

MyCalcWindow::MyCalcWindow(QWidget *parent) : QMainWindow (parent), chartWindow(nullptr){
    setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    connect(&tcpSocket, &QIODevice::readyRead, this, &MyCalcWindow::readMessage);
    connect(exitButton, SIGNAL(clicked()), this, SLOT(onQuit()));
}

MyCalcWindow::~MyCalcWindow(){
    if(chartWindow != nullptr){
        delete chartWindow;
    }
}

void MyCalcWindow::execute(){
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
    QString jsonString(jsonDocument.toJson(QJsonDocument::Compact));

    QByteArray jsonData = jsonString.toUtf8();

#ifdef DEBUG
    qDebug() << "=========== Mensagem Enviada ===========";
    qDebug() << "Msg: " << jsonData;
    qDebug() << "========================================";
#endif

    tcpSocket.write(jsonData);
}

void MyCalcWindow::on_execButton_clicked(void){
    execute();
}

void MyCalcWindow::on_radioButtonSoma_clicked(void){
    execute();
}

void MyCalcWindow::on_radioButtonSub_clicked(void){
    execute();
}

void MyCalcWindow::on_radioButtonMult_clicked(void){
    execute();
}

void MyCalcWindow::on_radioButtonDiv_clicked(void){
    execute();
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
    if(chartWindow != nullptr){
        chartWindow->close();
    }
}

void MyCalcWindow::readMessage(){
    tcpSocket.waitForReadyRead(-1);

    QByteArray jsonData = tcpSocket.readLine();
    QString jsonString = QString::fromStdString(jsonData.toStdString());

#ifdef DEBUG
    qDebug() << "========== Mensagem Recebida ===========";
    qDebug() << "Msg: " << jsonString;
    qDebug() << "========================================";
#endif

    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonObject jsonObject = jsonDocument.object();

    int answerType = jsonObject.value("answerType").toInt();
    switch (answerType) {
    case 1:
    {
        double resultado = jsonObject.value("result").toDouble();

#ifdef DEBUG
        qDebug() << "============== Resultado ==============";
        qDebug() << "Result: " << resultado;
        qDebug() << "========================================";
#endif

        QString resultString;
        resultString.setNum(resultado);
        textEditResult->setText(resultString);
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
    QString jsonString(jsonDocument.toJson(QJsonDocument::Compact));

    QByteArray jsonData = jsonString.toUtf8();

#ifdef DEBUG
    qDebug() << "=========== Mensagem Enviada ===========";
    qDebug() << "Msg: " << jsonData;
    qDebug() << "========================================";
#endif

    tcpSocket.write(jsonData);
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
    QString jsonString(jsonDocument.toJson(QJsonDocument::Compact));

    QByteArray jsonData = jsonString.toUtf8();

#ifdef DEBUG
    qDebug() << "=========== Mensagem Enviada ===========";
    qDebug() << "Msg: " << jsonData;
    qDebug() << "========================================";
#endif

    tcpSocket.write(jsonData);
}

void MyCalcWindow::showPieChart(QString title, vector<pair<QString, int>> operations){
    if(chartWindow != nullptr){
        chartWindow->close();
        delete chartWindow;
        chartWindow = nullptr;
    }
    QPieSeries *series = new QPieSeries();

    for(vector<pair<QString, int>>::iterator it = operations.begin(); it != operations.end(); ++it){
        series->append((*it).first, (*it).second);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(title);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    chartWindow = new QMainWindow();
    chartWindow ->setCentralWidget(chartView);
    chartWindow ->resize(400, 300);
    chartWindow ->show();
}
