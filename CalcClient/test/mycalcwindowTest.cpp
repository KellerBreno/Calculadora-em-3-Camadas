#include "mycalcwindowTest.h"

#define IP "192.168.2.4"
#define PORT 56145

MyCalcWindowTest::MyCalcWindowTest()
{

}

MyCalcWindowTest::~MyCalcWindowTest()
{

}

/**
 * @brief MyCalcWindowTest::setupMain
 *
 * Configura calculadora com parametros inicias ao usuario logar
 **/
void MyCalcWindowTest::setupMain(QString username, bool adminLevel, QString ip = IP, int port = PORT)
{
    calc.onUserLogin(username, adminLevel, ip, port);
}

void MyCalcWindowTest::casoUsoPrincipal_data()
{
    // ENTRADA
    QTest::addColumn<QString>("nome");
    QTest::addColumn<bool>("isAdm");
    QTest::addColumn<int>("timeWait");

    QTest::addColumn<QString>("v1_1");
    QTest::addColumn<QString>("v2_1");
    QTest::addColumn<QRadioButton*>("b_1");
    QTest::addColumn<QString>("r_1");
    QTest::addColumn<QString>("v1_2");
    QTest::addColumn<QPushButton*>("b_2");
    QTest::addColumn<QString>("r_2");
    QTest::addColumn<QRadioButton*>("b_3");
    QTest::addColumn<QString>("r_3");
    QTest::addColumn<QString>("v1_4");
    QTest::addColumn<QString>("v2_4");
    QTest::addColumn<QRadioButton*>("b_4");
    QTest::addColumn<QString>("r_4");

    QTest::newRow("acesso admin") << "admin" << true << 1000 << "3,0" << "2,5" << calc.radioButtonSoma << "5.5" << "4,0" << calc.execButton << "6.5" << calc.radioButtonSub << "1.5" << "4,0" << "2,0" << calc.radioButtonDiv << "2.0";
    QTest::newRow("acesso breno") << "breno" << false << 1000 << "3,0" << "2,5" << calc.radioButtonSoma << "5.5" << "4,0" << calc.execButton << "6.5" << calc.radioButtonSub << "1.5" << "0,0" << "1,0" << calc.radioButtonSoma << "1.0";
}

/**
 * @brief MyCalcWindowTest::casoUsoPrincipal
 *
 * Caso de Uso Principal
 * Usuario com acesso ao sistema realiza algumas operacoes, e de depois abre relatorios
 **/
void MyCalcWindowTest::casoUsoPrincipal()
{
    QFETCH(QString, nome);
    QFETCH(bool, isAdm);
    QFETCH(int, timeWait);

    setupMain(nome, isAdm);

    // operacao 1
    QFETCH(QString, v1_1);
    calc.input1->clear();
    QTest::keyClicks(calc.input1, v1_1, Qt::NoModifier, 50);

    QFETCH(QString, v2_1);
    calc.input2->clear();
    QTest::keyClicks(calc.input2, v2_1, Qt::NoModifier, 50);

    QFETCH(QRadioButton*, b_1);
    b_1->click();

    QTest::qWait(timeWait);
    QFETCH(QString, r_1);
    QCOMPARE(r_1, calc.textEditResult->toPlainText());

    // operacao 2
    QFETCH(QString, v1_2);
    calc.input1->clear();
    QTest::keyClicks(calc.input1, v1_2, Qt::NoModifier, 50);

    QFETCH(QPushButton*, b_2);
    b_2->click();

    QTest::qWait(timeWait);
    QFETCH(QString, r_2);
    QCOMPARE(r_2, calc.textEditResult->toPlainText());

    // operacao 3
    QFETCH(QRadioButton*, b_3);
    b_3->click();

    QTest::qWait(timeWait);
    QFETCH(QString, r_3);
    QCOMPARE(r_3, calc.textEditResult->toPlainText());

    // operacao 4
    QFETCH(QString, v1_4);
    calc.input1->clear();
    QTest::keyClicks(calc.input1, v1_4, Qt::NoModifier, 50);

    QFETCH(QString, v2_4);
    calc.input2->clear();
    QTest::keyClicks(calc.input2, v2_4, Qt::NoModifier, 50);

    QFETCH(QRadioButton*, b_4);
    b_4->click();

    QTest::qWait(timeWait);
    QFETCH(QString, r_4);
    QCOMPARE(r_4.toDouble(), calc.textEditResult->toPlainText().toDouble());

    // se eh adm, abre o grafico geral
    if (isAdm)
     {
         calc.actionAllUsers->trigger();
         bool resultWait = QTest::qWaitFor([&]() {
             return (calc.chartWindow != nullptr);
         });

         QCOMPARE(calc.chartWindow->isVisible(), isAdm);
         QCOMPARE(resultWait, isAdm);

         QTest::qWait(timeWait);

         calc.chartWindow->close();
         QCOMPARE(calc.chartWindow->isVisible(), false);

         calc.actionAllUsers->trigger(); // abre grafico total
         resultWait = QTest::qWaitFor([&]() {
             return (calc.chartWindow != nullptr);
         });

         QCOMPARE(resultWait, isAdm);

         QTest::qWait(timeWait);
     }
     else
     {
         // verifica se opcao de grafico geral esta ativa para usario nao admin
         QCOMPARE(calc.actionAllUsers->isVisible(), false);
     }

    // abre operacoes do usuario
    calc.actionByUser->trigger();
    bool resultWait = QTest::qWaitFor([&]() {
        return (calc.chartWindow != nullptr);
    });

    if (calc.chartWindow != nullptr) {
        qDebug() << calc.chartWindow->isVisible();
    }

    QCOMPARE(resultWait, true);

    QTest::qWait(timeWait);

    calc.onQuit(); // calc.close() n disparou SLOT
    resultWait = QTest::qWaitFor([&]() {
        return (calc.chartWindow == nullptr || (calc.chartWindow != nullptr && !calc.chartWindow->isVisible()));
    });
    QCOMPARE(resultWait, true);
}

/**
 * @brief MyCalcWindowTest::verificaRadioButtons
 *
 * Verifica se apenas um radioButton esta selecionado
 **/
void MyCalcWindowTest::verificaRadioButtons()
{
    calc.radioButtonSoma->click();
    QCOMPARE(calc.radioButtonSoma->isChecked(), true);
    QCOMPARE(calc.radioButtonDiv->isChecked(), false);
    QCOMPARE(calc.radioButtonMult->isChecked(), false);
    QCOMPARE(calc.radioButtonSub->isChecked(), false);

    calc.radioButtonDiv->click();
    QCOMPARE(calc.radioButtonDiv->isChecked(), true);
    QCOMPARE(calc.radioButtonSoma->isChecked(), false);
    QCOMPARE(calc.radioButtonMult->isChecked(), false);
    QCOMPARE(calc.radioButtonSub->isChecked(), false);

    calc.radioButtonMult->click();
    QCOMPARE(calc.radioButtonMult->isChecked(), true);
    QCOMPARE(calc.radioButtonDiv->isChecked(), false);
    QCOMPARE(calc.radioButtonSoma->isChecked(), false);
    QCOMPARE(calc.radioButtonSub->isChecked(), false);

    calc.radioButtonSub->click();
    QCOMPARE(calc.radioButtonSub->isChecked(), true);
    QCOMPARE(calc.radioButtonDiv->isChecked(), false);
    QCOMPARE(calc.radioButtonMult->isChecked(), false);
    QCOMPARE(calc.radioButtonSoma->isChecked(), false);
}

void MyCalcWindowTest::casoDeUsoAlternativo_data()
{
    // ENTRADA
    QTest::addColumn<QString>("user");
    QTest::addColumn<bool>("isAdm");
    QTest::addColumn<QString>("evento");
    // SAIDA
    QTest::addColumn<bool>("visivel"); // somente se quiser testar transição (parte importante do comportamento

    QTest::newRow("pressinou teclas ALT + F4") << "admin" << true << "alt+f4" << true;
    QTest::newRow("pressionou tecla ESCAPE") << "breno" << false << "esc" << true;
    QTest::newRow("clicou botão fechar") << "admin" << false << "close" << true;
}


/**
 * @brief MyCalcWindowTest::casoDeUsoAlternativo
 *
 * Caso de Uso Alternativo
 * Usuario com acesso ao sistema preciona alumas teclas para sair do sistema
 **/
void MyCalcWindowTest::casoDeUsoAlternativo()
{
    QFETCH(QString, user);
    QFETCH(bool, isAdm);
    QFETCH(QString, evento);
    QFETCH(bool, visivel);

    setupMain(user, isAdm);
    calc.show();

    if(evento =="esc")
        QApplication::sendEvent(&calc, new QKeyEvent(QEvent::KeyPress  , Qt::Key_Escape, Qt::NoModifier) );
    else
        QApplication::sendEvent(&calc, new QCloseEvent());

    //qDebug() << "DIALOGO ABERTO: expected " << visivel << " == " << d.isVisible();
    QCOMPARE(visivel, calc.isVisible());

    if (calc.chartWindow != nullptr)
    {
        QCOMPARE(visivel, calc.chartWindow->isVisible());
    }
}

QTEST_MAIN(MyCalcWindowTest)
//#include "MyCalcWindowTest.moc"
