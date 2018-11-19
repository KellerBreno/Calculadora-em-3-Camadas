/*!
 * \file mycalcwindow.h
 * Arquivo contendo a declaração da Classe MyCalcWindow.
 */

#ifndef MYCALCSCREEN_H
#define MYCALCSCREEN_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <data/user.h>

#include <QJsonObject>
#include <utility>
#include <vector>

#include "ui_calcwindow.h"

QT_CHARTS_USE_NAMESPACE

using namespace std;

/*!
 * \class MyCalcWindow
 * \brief Classe para gerenciar as ações de uma calculadora.
 *
 * Esta classe gerencia as iterações do usuário com uma calculadora e delega todas suas operações a serem feitas no servidor.
 *
 */
class MyCalcWindow : public QMainWindow, private Ui::CalcWindow{
    Q_OBJECT

    /*!
     * \brief Classe para Testes do MyLoginDialog.
     */
    friend class MyLoginDialogTest;
    /*!
     * \brief Classe para Testes do MyCalcWindow.
     */
    friend class MyCalcWindowTest;

public:
    MyCalcWindow(QWidget *parent = nullptr);
    virtual ~MyCalcWindow();

public slots:
    void on_execButton_clicked(void);
    void on_radioButtonAdd_clicked(void);
    void on_radioButtonSub_clicked(void);
    void on_radioButtonMult_clicked(void);
    void on_radioButtonDiv_clicked(void);
    void on_actionByUser_triggered(void);
    void on_actionAllUsers_triggered(void);
    void on_userRole_currentIndexChanged(int);
    void onUserLogin(User *user);
    void onQuit(void);
    void readMessage(QJsonObject jsonObject);

private:
    void execute(void);
    void showPieChart(QString title, vector<pair<QString, int>> operations);
    void setupUserUi(int roleCode);

    User *user;

    /*!
     * \brief TCPSocket utilizado pela aplicação para comunicar com servidor.
     */
    QTcpSocket tcpSocket;

    /*!
     * \brief MainWindow auxiliar para exibição de gráficos de operações.
     */
    QMainWindow* chartWindow;

    /*!
     * \brief Flag numerica representando o papel usuário
     */
    static const int USER = 0;

    /*!
     * \brief Flag numerica representando o papel administrador
     */
    static const int ADMIN = 1;
};

#endif // MYCALCEXAMPLE_H
