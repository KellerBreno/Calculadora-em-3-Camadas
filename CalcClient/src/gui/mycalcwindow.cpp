/*!
 * \file mycalcwindow.cpp
 * Arquivo contendo a implementação da Classe MyCalcWindow.
 */

/*!
 * \def DEBUG
 * Flag demarcando se as mensagens de debug devem ou não serem exibidas.
 */
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

#include <control/calculadora.h>

#include "mycalcwindow.h"
#include "ui_calcwindow.h"

/*!
 * \brief Construtor Padrão para a classe MyCalcWindow.
 *
 * Esse construtor inicializa os atributos parent e chartWindow. Além disso, o construtor configura a interface por meio do método 'setupUi'
 * da classe pai CalcWindow e conecta os slots para a leitura de mensagens do servidor e saída da aplicação.
 *
 * \param parent Referência ao componente pai.
 *
 */
MyCalcWindow::MyCalcWindow(QWidget *parent) : QMainWindow (parent), chartWindow(nullptr){
    setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    connect(exitButton, SIGNAL(clicked()), this, SLOT(onQuit()));
}

/*!
 * \brief Destrutor da classe MyCalcWindow
 *
 * Esse destrutor é utilizado para deletar a referência contida em chartWindow.
 *
 */
MyCalcWindow::~MyCalcWindow(){
    if(chartWindow != nullptr){
        delete chartWindow;
    }
}

/*!
 * \brief Método privado para coleta dos dados e envio ao servidor para realização de operações.
 *
 * Este método extrai os dados da interface e solicita a execução da operação para o NetworkManager.
 *
 * \sa MyCalcWindow::on_execButton_clicked(), MyCalcWindow::on_radioButtonSoma_clicked(), MyCalcWindow::on_radioButtonSub_clicked(),
 * MyCalcWindow::on_radioButtonMult_clicked(), MyCalcWindow::on_radioButtonDiv_clicked(), MyCalcWindow::readMessage().
 */
void MyCalcWindow::execute(){
    double parcela1 = input1->value();
    double parcela2 = input2->value();

    int opCode;
    if(radioButtonAdd->isChecked()){
        opCode = 1;
    } else if(radioButtonSub->isChecked()){
        opCode = 2;
    } else if(radioButtonMult->isChecked()){
        opCode = 3;
    } else if(radioButtonDiv->isChecked()){
        opCode = 4;
    }

    Calculadora *networkManager = Calculadora::getInstance();
    BasicUser *basicUser = (BasicUser*) user->asRole(BasicUser::BASIC_USER_NAME);
    networkManager->doOperation(basicUser,parcela1,parcela2,opCode);
}

/*!
 * \brief Slot chamado quando se clica no botão 'Executar' e executa uma operação.
 *
 * \sa MyCalcWindow::execute().
 */
void MyCalcWindow::on_execButton_clicked(void){
    execute();
}

/*!
 * \brief Slot chamado quando se clica no radio button da operação soma.
 *
 * \sa MyCalcWindow::execute().
 */
void MyCalcWindow::on_radioButtonAdd_clicked(void){
    execute();
}

/*!
 * \brief Slot chamado quando se clica no radio button da operação subtração.
 *
 * \sa MyCalcWindow::execute().
 */
void MyCalcWindow::on_radioButtonSub_clicked(void){
    execute();
}

/*!
 * \brief Slot chamado quando se clica no radio button da operação multiplicação.
 *
 * \sa MyCalcWindow::execute().
 */
void MyCalcWindow::on_radioButtonMult_clicked(void){
    execute();
}

/*!
 * \brief Slot chamado quando se clica no radio button da operação divisão.
 *
 * \sa MyCalcWindow::execute().
 */
void MyCalcWindow::on_radioButtonDiv_clicked(void){
    execute();
}

/*!
 * \brief Slot chamado para se configurar a calculadora sobre informações de rede e usuário.
 * \param user Referencia ao usuário da aplicação.
 */
void MyCalcWindow::onUserLogin(User* user){
    setEnabled(true); 
    this->user = user;
    AdminUser *adminUser = (AdminUser*) this->user->asRole(AdminUser::ADMIN_USER_NAME);
    if(adminUser!=nullptr){
        setupUserUi(ADMIN);
    }else{
        setupUserUi(USER);
    }
    connect(Calculadora::getInstance()->getQObject(), SIGNAL(messageReceive(QJsonObject)), this, SLOT(readMessage(QJsonObject)));
}

/*!
 * \brief Slot chamado ao se clicar no botão 'Sair'.
 */
void MyCalcWindow::onQuit(void){
    close();
    if(chartWindow != nullptr){
        chartWindow->close();
    }
}

/*!
 * \brief Slot chamado quando o socket recebe uma mensagem de resposta do servidor.
 *
 * Ao receber uma resposta do NetworkManager, este método extrai as informações da mensagem e realiza a operação correspondente.
 *
 * \sa MyCalcWindow::execute(), MyCalcWindow::on_actionAllUsers_triggered(), MyCalcWindow::on_actionByUser_triggered().
 */
void MyCalcWindow::readMessage(QJsonObject jsonObject){
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
        resultEdit->setText(resultString);
    }
        break;
    case 2:
    {
        vector<pair<QString, int>> operations;

        operations.push_back(make_pair("Adição", jsonObject.value("Adição").toInt()));
        operations.push_back(make_pair("Subtração", jsonObject.value("Subtração").toInt()));
        operations.push_back(make_pair("Multiplicação", jsonObject.value("Multiplicação").toInt()));
        operations.push_back(make_pair("Divisão", jsonObject.value("Divisão").toInt()));

        showPieChart("Operações feitas pelo Usuário: " + user->getUsername(), operations);
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

/*!
 * \brief Slot chamado quando selecionada a opção do menu 'Por Usuário'.
 *
 * Esse slot faz uma requisição ao NetworkManager dos dados de todas as operações realizadas pelo usuário.
 *
 * \sa MyCalcWindow::readMessage(), MyCalcWindow::showPieChart(QString, vector<pair<QString, int>>).
 */
void MyCalcWindow::on_actionByUser_triggered(void){
    Calculadora *networkManager = Calculadora::getInstance();
    BasicUser *basicUser = (BasicUser*) user->asRole(BasicUser::BASIC_USER_NAME);
    networkManager->reportByUser(basicUser);
}

/*!
 * \brief Slot chamado quando selecionada a opção do menu 'Todos os Usuários'.
 *
 * Esse slot faz uma requisição ao NetworkManager dos dados de todas as operações realizadas por todos os usuários.
 *
 * \sa MyCalcWindow::readMessage(), MyCalcWindow::showPieChart(QString, vector<pair<QString, int>>).
 */
void MyCalcWindow::on_actionAllUsers_triggered(void){
    AdminUser *adminUser = (AdminUser*) user->asRole(AdminUser::ADMIN_USER_NAME);
    if(adminUser == nullptr){
        return;
    }
    Calculadora *networkManager = Calculadora::getInstance();
    networkManager->reportAllUsers(adminUser);
}

/*!
 * \brief Método para delegar a atualização da interface dado uma mudança de papel do usuário
 * \param position Opção selecionada no combo box
 */
void MyCalcWindow::on_userRole_currentIndexChanged(int position){
    switch (position) {
    case 0:
        setupUserUi(USER);
        break;
    case 1:
        AdminUser *adminUser = (AdminUser*) user->asRole(AdminUser::ADMIN_USER_NAME);
        if(adminUser == nullptr){
            QMessageBox::critical(this, "CalcWindow", "Você não pode realizar essa operação", QMessageBox::Ok);
            setupUserUi(USER);
            return;
        }
        setupUserUi(ADMIN);
        break;
    }
}

/*!
 * \brief Método é utilizado para se gerar exibições em gráfico pizza das operações realizadas, sejam por todos os usuários ou somente um deles.
 * \param title Título do gráfico.
 * \param operations Vetor contendo os dados das operações em pares (Operação, Quantidade).
 *
 * \sa MyCalcWindow::on_actionByUser_triggered(), MyCalcWindow::on_actionAllUser_triggered().
 */
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

/*!
 * \brief Método para alterar a interface baseado no papel do usuário
 * \param roleCode código do papel do usuário
 */
void MyCalcWindow::setupUserUi(int roleCode){
    switch (roleCode) {
    case USER:
        actionAllUsers->setEnabled(false);
        actionByUser->setEnabled(true);
        input1->setEnabled(true);
        input2->setEnabled(true);
        resultEdit->setEnabled(true);
        groupBox->setEnabled(true);
        execButton->setEnabled(true);
        userRole->setCurrentIndex(0);
        break;
    case ADMIN:
        actionAllUsers->setEnabled(true);
        actionByUser->setEnabled(false);
        input1->setEnabled(false);
        input2->setEnabled(false);
        resultEdit->setEnabled(false);
        groupBox->setEnabled(false);
        execButton->setEnabled(false);
        userRole->setCurrentIndex(1);
        break;
    }
}
