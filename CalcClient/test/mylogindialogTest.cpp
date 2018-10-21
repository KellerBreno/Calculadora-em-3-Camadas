#define IP "192.168.2.4"
#define PORT "56145"

#include "mylogindialogTest.h"

MyLoginDialogTest::MyLoginDialogTest()
{

}

MyLoginDialogTest::~MyLoginDialogTest()
{

}

/**
 * @brief MyLoginDialogTest::setupMain
 *
 * Configura tela inicial de acordo com configuracoes setadas no main
 **/
void MyLoginDialogTest::setupMain()
{
    calc.setEnabled(false);
    QObject::connect(&d, SIGNAL(logged(QString, bool, QString, int)), &calc, SLOT(onUserLogin(QString, bool, QString, int)));
    QObject::connect(&d, SIGNAL(quit(void)), &calc, SLOT(onQuit(void)));

    calc.show();
    d.show();
}

void MyLoginDialogTest::casoUsoPrincipal_data()
{
    // ENTRADA
    QTest::addColumn<QString>("nome");
    QTest::addColumn<QString>("senha");
    QTest::addColumn<QString>("ip");
    QTest::addColumn<QString>("porta");
    QTest::addColumn<QString>("mensagem");
    QTest::addColumn<bool>("canEnter");
    QTest::addColumn<bool>("isAdm");
    QTest::addColumn<int>("time");

    QTest::newRow("login vazio") << "" << "" << IP << PORT << "Por favor preencha todos campos acima" << false << false << 1000;
    QTest::newRow("login admin ip vazio") << "admin" << "123" << "" << PORT << "Por favor preencha todos campos acima" << false << true << 1000;
    QTest::newRow("login ip/porta errados") << "admin" << "admin" << "192.666.666.22" << (PORT + 1) << "" << false << false << 1000;
    QTest::newRow("login admin") << "admin" << "admin" << IP << PORT << "Seja Bem Vindo, admin" << true << true << 1000;
    QTest::newRow("login breno") << "breno" << "keller" << IP << PORT << "Seja Bem Vindo, breno" << true << false  << 1000;
    QTest::newRow("login incorreto breno2") << "breno2" << "keller" << IP << PORT << "Credenciais Incorretas" << false  << false << 1000;
    QTest::newRow("login incorreto admin") << "admin" << "passwd" << IP << PORT << "Credenciais Incorretas" << false << false  << 1000;
}

/**
 * @brief MyLoginDialogTest::casoUsoPrincipal
 *
 * Caso de Uso Principal
 * Usuarios sem credenciais ou que nao conhecem o endereco do servidor nao podem conseguir logar
 * Os que logam, apenas os adiminstradores podem acessar o relatorios de todos usuarios
 **/
void MyLoginDialogTest::casoUsoPrincipal()
{
    setupMain();

    QFETCH(QString, nome);
    QFETCH(QString, senha);
    QFETCH(QString, ip);
    QFETCH(QString, porta);
    QFETCH(QString, mensagem);
    QFETCH(bool, canEnter);
    QFETCH(bool, isAdm);
    QFETCH(int, time);

    QTest::keyClicks(d.user_input_line, nome, Qt::NoModifier, 50);
    QTest::keyClicks(d.password_input_line, senha, Qt::NoModifier, 50);
    QTest::keyClicks(d.ip_input_line, ip, Qt::NoModifier, 50);
    QTest::keyClicks(d.port_input_line, porta, Qt::NoModifier, 50);

    // abre tratamento em outra instancia para verificar saida e fechar QMessageBox
    QTimer::singleShot(500, this, SLOT(timeOut()));

    msgResult = mensagem;
    qDebug() << msgResult;
    QTest::mouseClick(d.login_button, Qt::LeftButton);

    bool resultWait = QTest::qWaitFor([&]() {
        return !d.isVisible();
    }, time);

    //qDebug() << resultWait << "|" << canEnter;
    QCOMPARE(resultWait, canEnter);
    QCOMPARE(calc.isEnabled(), canEnter);

    verificaCamposCalcWindow(canEnter);
    verificaQActionCalcWindow(canEnter, isAdm);
}

/**
 * @brief MyLoginDialogTest::clearInputs
 *
 * Limpa campos de input da tela de login
 */
void MyLoginDialogTest::clearInputs()
{
    d.user_input_line->clear();
    d.password_input_line->clear();
    d.ip_input_line->clear();
    d.port_input_line->clear();
}

/**
 * @brief MyLoginDialogTest::casoUsoSanidade
 *
 * Testa se campos foram criados corretamnete ao iniciae, e se tela da calculadora esta ativa
 */
void MyLoginDialogTest::casoUsoSanidade()
{
    setupMain();

    QCOMPARE(d.isVisible(), true);
    QCOMPARE(d.isEnabled(), true);

    QCOMPARE(d.isModal(), false);

    QCOMPARE(calc.isVisible(), true);
    QCOMPARE(calc.isEnabled(), false);

    QVERIFY2(d.user_input_line, "campo usuario nao foi criado ");
    QVERIFY2(d.password_input_line, "campo senha nao foi criado ");
    QVERIFY2(d.ip_input_line, "campo ip nao foi criado ");
    QVERIFY2(d.port_input_line, "campo porta nao foi criado ");

    QVERIFY2(d.login_button, "botao login nao foi criado ");
    QVERIFY2(d.cancel_button, "botao porta nao foi criado ");

    verificaCamposCalcWindow(false);
}

/**
 * @brief MyLoginDialogTest::verificaCamposCalcWindow
 * @param active estado esperado
 *
 * Verifica se campos da tela de calculadora estao no estado esperado
 */
void MyLoginDialogTest::verificaCamposCalcWindow(bool active)
{
    QVERIFY2(calc.input1, "campo input1 nao foi criado ");
    QCOMPARE(calc.input1->isEnabled(), active);

    QVERIFY2(calc.input2, "campo input2 nao foi criado ");
    QCOMPARE(calc.input2->isEnabled(), active);

    QVERIFY2(calc.input2, "campo input2 nao foi criado ");
    QCOMPARE(calc.input2->isEnabled(), active);

    QVERIFY2(calc.textEditResult, "campo textEditResult nao foi criado ");
    QCOMPARE(calc.textEditResult->isEnabled(), active);

    QVERIFY2(calc.execButton, "botao execButton nao foi criado ");
    QCOMPARE(calc.execButton->isEnabled(), active);

    QVERIFY2(calc.exitButton, "botao exitButton nao foi criado ");
    QCOMPARE(calc.exitButton->isEnabled(), active);

    QVERIFY2(calc.radioButtonSoma, "radioButtonSoma nao foi criado ");
    QCOMPARE(calc.radioButtonSoma->isEnabled(), active);

    QVERIFY2(calc.radioButtonDiv, "radioButtonDiv nao foi criado ");
    QCOMPARE(calc.radioButtonDiv->isEnabled(), active);

    QVERIFY2(calc.radioButtonMult, "radioButtonMult nao foi criado ");
    QCOMPARE(calc.radioButtonMult->isEnabled(), active);

    QVERIFY2(calc.radioButtonSub, "radioButtonSub nao foi criado ");
    QCOMPARE(calc.radioButtonSub->isEnabled(), active);

    QVERIFY2(calc.actionAllUsers, "menu actionAllUsers nao foi criado ");
    QVERIFY2(calc.actionByUser, "menu actionByUser nao foi criado ");
}

/**
 * @brief MyLoginDialogTest::verificaQActionCalcWindow
 * @param active estado esperado dos campos
 * @param isAdm se o usuario eh administrado
 *
 * Verifica se menu geral so apararece para usuarios admin, e se o do usuario aparece para todos
 */
void MyLoginDialogTest::verificaQActionCalcWindow(bool active, bool isAdm)
{
    if(active)
    {
        if (isAdm)
        {
            QCOMPARE(calc.actionAllUsers->isVisible(), true);
        }
        else
        {
            QCOMPARE(calc.actionAllUsers->isVisible(), false);
        }

        QCOMPARE(calc.actionByUser->isVisible(), true);
    }
}


void MyLoginDialogTest::casoDeUsoAlternativo_data()
{
    // ENTRADA
    QTest::addColumn<QString>("evento");
    // SAIDA
    QTest::addColumn<bool>("visivel"); // somente se quiser testar transição (parte importante do comportamento

    QTest::newRow("pressinou teclas ALT + F4") << "alt+f4" << true;
    QTest::newRow("pressionou tecla ESCAPE")  << "esc" << true;
    QTest::newRow("clicou botão fechar") << "close" << true;
}

/**
 * @brief MyLoginDialogTest::casoDeUsoAlternativo
 *
 * Alumas teclas sao precionada na tela de login para sair do sistema
 */
void MyLoginDialogTest::casoDeUsoAlternativo()
{
    QFETCH(QString, evento);
    QFETCH(bool, visivel);

    setupMain();
    d.show();
    calc.show();

    if(evento =="esc")
        QApplication::sendEvent(&d, new QKeyEvent(QEvent::KeyPress  , Qt::Key_Escape, Qt::NoModifier) );
    else
        QApplication::sendEvent(&d, new QCloseEvent());

    //qDebug() << "DIALOGO ABERTO: expected " << visivel << " == " << d.isVisible();
    QCOMPARE(visivel, d.isVisible());
    QCOMPARE(visivel, calc.isVisible());

    if (calc.chartWindow != nullptr)
    {
        QCOMPARE(visivel, calc.chartWindow->isVisible());
    }
}

void MyLoginDialogTest::timeOut()
{
    if(msgResult != "")
    {
        // Verificar e fechar message box, essa quando abrem sao modais
        QWidgetList allToplevelWidgets = QApplication::topLevelWidgets();
        foreach (QWidget *w, allToplevelWidgets)
        {
            if (w->inherits("QMessageBox")) {
               QMessageBox *mb = qobject_cast<QMessageBox *>(w);
               //qDebug() << "MessageBox: " << mb << mb->text() << "::" << msgResult;
               QCOMPARE(mb->text(), msgResult);
               qDebug() << mb->text();
               mb->close();
            }
        }
    }

    clearInputs(); // limpa valores dos campos input
    msgResult = "";
}

QTEST_MAIN(MyLoginDialogTest)
//#include "mylogindialogTest.moc"
