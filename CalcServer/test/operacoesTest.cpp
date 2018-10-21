#include "OperacoesTest.h"

OperacoesTest::OperacoesTest()
{
    workertThread  = new WorkerThread();
    workertThread->databaseHelper = new DatabaseHelperImpl();
}

OperacoesTest::~OperacoesTest()
{

}

void OperacoesTest::casoUsoRelatorios_data()
{
    QTest::addColumn<QString>("user");
    QTest::addColumn<bool>("canSee");

    QTest::newRow("Usuario admin") << "admin" << true;
    QTest::newRow("Usuario nao admin breno") << "breno" << false;
    QTest::newRow("Usuario nao existente ADMIN") << "ADMIN" << false;
}
/**
 * @brief OperacoesTest::casoUsoRelatorios
 *
 * Testa se usuario consegue acesso aos relatorios, apenas admin pode acessar
*/
void OperacoesTest::casoUsoRelatorios()
{
    QFETCH(QString, user);
    QFETCH(bool, canSee);

    int allOperationCode;
    if (canSee)
    {
        allOperationCode = 3;
    }
    else
    {
        allOperationCode = 4;
    }

    QJsonObject jsonResposta = workertThread->menu(getAllOperation(user));
    int answer = jsonResposta.value("answerType").toInt();
    QCOMPARE(answer, allOperationCode);
}

void OperacoesTest::casoUsoInserts_data()
{
    QTest::addColumn<QString>("user");
    QTest::addColumn<double>("v1");
    QTest::addColumn<double>("v2");
    QTest::addColumn<int>("opCode");

    QTest::addColumn<double>("result");

    QTest::newRow("Usuario admin soma 1 + 1") << "admin" << 1.0 << 1.0 << 1 << 2.0;
    QTest::newRow("Usuario admin soma 1 - 2") << "admin" << 1.0 << 2.0 << 2 << -1.0;
    QTest::newRow("Usuario tiago div 1 / 2") << "tiago" << 1.0 << 2.0 << 4 << 0.5;
    QTest::newRow("Usuario breno soma 4 - 2") << "breno" << 4.0 << 2.0 << 2 << 2.0;
    QTest::newRow("Usuario tiago soma 1 - 2") << "tiago" << 1.0 << 2.0 << 2 << -1.0;
    QTest::newRow("Usuario admin mult 12 * 10") << "admin" << 12.0 << 10.0 << 3 << 120.0;
    QTest::newRow("Usuario breno div 1 / 2") << "breno" << 1.0 << 2.0 << 4 << 0.5;
}

/**
 * @brief OperacoesTest::casoUsoInserts
 *
 * Verifica se inserts passadosa reetornam valores corretos e veirifca contagem final utilizando getAllOperations e getUserOperations
 */
void OperacoesTest::casoUsoInserts()
{
    QFETCH(QString, user);
    QFETCH(double, v1);
    QFETCH(double, v2);
    QFETCH(int, opCode);
    QFETCH(double, result);

    // pega valores antes do insert
    QJsonObject jsonTotal = workertThread->menu(getAllOperation("admin"));
    int numOperacoesTotais = contaOperacoes(jsonTotal);

    QJsonObject jsonResposta = workertThread->menu(getAllOperationUser(user));
    int numOperacoesTotaisUser = contaOperacoes(jsonResposta);

    int numOperacoes;
    int numTipoOperacoesTotal;
    switch(opCode)
    {
        case 1:
            numOperacoes = contaOperacoesOp(jsonResposta, "Adição");
            numTipoOperacoesTotal = contaOperacoesOp(jsonTotal, "Adição");
            break;
        case 2:
            numOperacoes = contaOperacoesOp(jsonResposta, "Subtração");
            numTipoOperacoesTotal = contaOperacoesOp(jsonTotal, "Subtração");
            break;
        case 3:
            numOperacoes = contaOperacoesOp(jsonResposta, "Multiplicação");
            numTipoOperacoesTotal = contaOperacoesOp(jsonTotal, "Multiplicação");
            break;
        case 4:
            numOperacoes = contaOperacoesOp(jsonResposta, "Divisão");
            numTipoOperacoesTotal = contaOperacoesOp(jsonTotal, "Divisão");
            break;
    }

    // insert
    jsonResposta = workertThread->menu(insert(user, v1, opCode, v2));
    int answer = jsonResposta.value("answerType").toInt();
    QCOMPARE(answer, 1);

    double answerV = jsonResposta.value("result").toDouble();
    QCOMPARE(answerV, result);

    // pega valores pos do insert e compara se houve acrescimo apenas no tipo da operacao desejada para aquele usuario
    jsonTotal = workertThread->menu(getAllOperation("admin"));
    QCOMPARE(contaOperacoes(jsonTotal) - numOperacoesTotais, 1);

    jsonResposta = workertThread->menu(getAllOperationUser(user));
    QCOMPARE(contaOperacoes(jsonResposta) - numOperacoesTotaisUser, 1);

    switch(opCode)
    {
        case 1:
            QCOMPARE(contaOperacoesOp(jsonResposta, "Adição") - numOperacoes, 1);

            QCOMPARE(contaOperacoesOp(jsonTotal, "Adição") - numTipoOperacoesTotal, 1);
            break;
        case 2:
            QCOMPARE(contaOperacoesOp(jsonResposta, "Subtração") - numOperacoes, 1);

            QCOMPARE(contaOperacoesOp(jsonTotal, "Subtração") - numTipoOperacoesTotal, 1);
            break;
        case 3:
            QCOMPARE(contaOperacoesOp(jsonResposta, "Multiplicação") - numOperacoes, 1);

            QCOMPARE(contaOperacoesOp(jsonTotal, "Multiplicação") - numTipoOperacoesTotal, 1);
            break;
        case 4:
            QCOMPARE(contaOperacoesOp(jsonResposta, "Divisão") - numOperacoes, 1);

            QCOMPARE(contaOperacoesOp(jsonTotal, "Divisão") - numTipoOperacoesTotal, 1);
            break;
    }
}

void OperacoesTest::casoUsoOperacoesUsuario_data()
{
    // ENTRADA
    QTest::addColumn<QString>("user");
    QTest::addColumn<QString>("senha");
    QTest::addColumn<bool>("loginOk");
    QTest::addColumn<bool>("canGetAllOperations");
    QTest::addColumn<bool>("testaInserts");
    QTest::addColumn<double>("v1");
    QTest::addColumn<double>("v2");
    QTest::addColumn<double>("resultAdd");
    QTest::addColumn<double>("resultSub");
    QTest::addColumn<double>("resultMult");
    QTest::addColumn<double>("resultDiv");

    QTest::newRow("Usuario admin valido com 4 operacoes") << "admin" << "admin" << true << true << true << 2.0 << 2.0 << 4.0 << 0.0 << 4.0 << 1.0;
    QTest::newRow("Usuario admin nao valido sem operacoes") << "admin" << "aDmin" << false << true << false << 2.0 << 2.0 << 4.0 << 0.0 << 4.0 << 1.0;
    QTest::newRow("Usuario nao admin com 4 operacoes") << "tiago" << "carneiro" << true << false << true << 10.0 << 2.0 << 12.0 << 8.0 << 20.0 << 5.0;
    QTest::newRow("Usuario nao valido sem operacoes") << "tiago2" << "carneiro" << false << false << false << 10.0 << 2.0 << 12.0 << 8.0 << 20.0 << 5.0;
}

/**
 * @brief OperacoesTest::casoUsoOperacoesUsuario
 *
 * Verifica usuario/senha e faz uma operaco de cada caso esse tenha acesso
 */
void OperacoesTest::casoUsoOperacoesUsuario()
{
    QFETCH(QString, user);
    QFETCH(QString, senha);
    QFETCH(bool, loginOk);

    QJsonObject jsonResposta;

    jsonResposta = workertThread->menu(loginUser(user, senha));
    bool valid = jsonResposta.value("valid").toBool();
    QCOMPARE(valid, loginOk);

    QFETCH(bool, canGetAllOperations);
    int allOperationCode;
    if (canGetAllOperations)
    {
        allOperationCode = 3;
    }
    else
    {
        allOperationCode = 4;
    }

    jsonResposta = workertThread->menu(getAllOperation(user));
    int answer = jsonResposta.value("answerType").toInt();
    QCOMPARE(answer, allOperationCode);

    QFETCH(bool, testaInserts);

    if (testaInserts)
    {
        // isAdmi
        int operacoesTotais = 0;
        if (canGetAllOperations)
        {
            jsonResposta = workertThread->menu(getAllOperation(user));
            operacoesTotais = contaOperacoes(jsonResposta);
        }

        jsonResposta = workertThread->menu(getAllOperationUser(user));
        int operacoesIniciaisUser = contaOperacoes(jsonResposta);

        QFETCH(double, v1);
        QFETCH(double, v2);
        QFETCH(double, resultAdd);
        QFETCH(double, resultSub);
        QFETCH(double, resultMult);
        QFETCH(double, resultDiv);

        // adicao
        jsonResposta = workertThread->menu(insert(user, v1, 1, v2));
        answer = jsonResposta.value("answerType").toInt();
        QCOMPARE(answer, 1);

        double answerV = jsonResposta.value("result").toDouble();
        QCOMPARE(answerV, resultAdd);

        // subtracao
        jsonResposta = workertThread->menu(insert(user, v1, 2, v2));
        answer = jsonResposta.value("answerType").toInt();
        QCOMPARE(answer, 1);

        answerV = jsonResposta.value("result").toDouble();
        QCOMPARE(answerV, resultSub);

        // multiplicaco
        jsonResposta = workertThread->menu(insert(user, v1, 3, v2));
        answer = jsonResposta.value("answerType").toInt();
        QCOMPARE(answer, 1);

        answerV = jsonResposta.value("result").toDouble();
        QCOMPARE(answerV, resultMult);

        // divisao
        jsonResposta = workertThread->menu(insert(user, v1, 4, v2));
        answer = jsonResposta.value("answerType").toInt();
        QCOMPARE(answer, 1);

        answerV = jsonResposta.value("result").toDouble();
        QCOMPARE(answerV, resultDiv);

        jsonResposta = workertThread->menu(getAllOperationUser(user));
        qDebug() << "Finais: " << contaOperacoes(jsonResposta);
        int operacoesTotaisUser = contaOperacoes(jsonResposta) - operacoesIniciaisUser;

        QCOMPARE(operacoesTotaisUser, 4);

        // isAdmi
        if (canGetAllOperations) {
            jsonResposta = workertThread->menu(getAllOperation(user));

            QCOMPARE(contaOperacoes(jsonResposta) - operacoesTotais, operacoesTotaisUser);
        }
    }


}

/**
 *
 * Cria json operaco de buscar todas operacoes de todos usuarios
 *
 * @brief OperacoesTest::getAllOperation
 * @param user
 * @return json montado
 */
QJsonObject OperacoesTest::getAllOperation(QString user)
{
    QJsonObject jsonObject;
    jsonObject.insert("operationType", 4);
    jsonObject.insert("username", user);

    return jsonObject;
}

/**
 * @brief OperacoesTest::getAllOperationUser
 *
 * Cria json operaco de buscar todas operacoes do usuario
 *
 * @param user
 * @return json montado
 */
QJsonObject OperacoesTest::getAllOperationUser(QString user)
{
    QJsonObject jsonObject;
    jsonObject.insert("operationType", 3);
    jsonObject.insert("username", user);

    return jsonObject;
}

/**
 * @brief OperacoesTest::loginUser
 *
 * Cria json operaco de loginUser
 *
 * @param user
 * @param passwd
 * @return json montado
 */
QJsonObject OperacoesTest::loginUser(QString user, QString passwd)
{
    QJsonObject jsonObject;
    jsonObject.insert("operationType", 1);
    jsonObject.insert("username", user);
    jsonObject.insert("password", passwd);

    return jsonObject;
}

/**
 * @brief OperacoesTest::insert
 *
 * Cria json operaco de insertOperation
 *
 * @param user
 * @param v1
 * @param opCode
 * @param v2
 * @return json montado
 */
QJsonObject OperacoesTest::insert(QString user, double v1, int opCode, double v2)
{
    QJsonObject jsonObject;
    jsonObject.insert("operationType", 2);
    jsonObject.insert("username", user);
    jsonObject.insert("v1", v1);
    jsonObject.insert("opCode", opCode);
    jsonObject.insert("v2", v2);

    return jsonObject;
}

/**
 * @brief OperacoesTest::contaOperacoes
 *
 * Retorna o numero de operacoes presentes no json
 *
 * @param json com operacoes
 * @return int numero de operacoes
 */
int OperacoesTest::contaOperacoes(QJsonObject json)
{
    int sum = json.value("Adição").toInt();
    sum += json.value("Subtração").toInt();
    sum += json.value("Multiplicação").toInt();
    sum += json.value("Divisão").toInt();

    return sum;
}

/**
 * @brief OperacoesTest::contaOperacoesOp
 *
 * Retorna o numero de operacoes desejada presentes no json
 *
 * @param json com opercaoes
 * @param op operacao desejada
 * @return int numero de opercoes do tipo desejado
 */
int OperacoesTest::contaOperacoesOp(QJsonObject json, QString op)
{
    return json.value(op).toInt();
}

QTEST_MAIN(OperacoesTest)
//#include "OperacoesTest.moc"
