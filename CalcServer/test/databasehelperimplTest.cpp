#include "databasehelperimplTest.h"

DatabaseHelperImplTest::DatabaseHelperImplTest()
{

}

DatabaseHelperImplTest::~DatabaseHelperImplTest()
{
    if (db.sqlDatabase.open()) {
      db.sqlDatabase.close();
    }
}

/**
 * @brief DatabaseHelperImplTest::casoUsoConectaBanco
 *
 * Testa se bando do arquivo exites e se eh possivel acessa-lo
 * Verifica funiconamento do metodo setupDatabase()
 */
void DatabaseHelperImplTest::casoUsoConectaBanco()
{
    QString path = QFINDTESTDATA("calc_example.sqlite");
    // qDebug() << path;

    QFile myFile(path);
    int size = 0;
    if (myFile.open(QIODevice::ReadOnly))
    {
        size = myFile.size();  //when file does open.
        myFile.close();
    }

    QVERIFY(size > 0);

    db.setupDatabase();

    bool isOpened = db.sqlDatabase.open();

    QVERIFY(isOpened == true);

    if (isOpened) {
      db.sqlDatabase.close();
    }
}
void DatabaseHelperImplTest::casoUsoGetUsuario_data()
{
    // ENTRADA
    QTest::addColumn<QString>("nome");
    // SAIDA
    QTest::addColumn<int>("id");

    QTest::newRow("login admin") << "admin" << 1;
    QTest::newRow("login breno") << "breno" << 2;
    QTest::newRow("login tiago") << "tiago" << 3;
    QTest::newRow("login inexistente tiago2") << "tiago2" << 0;
}

/**
 * @brief DatabaseHelperImplTest::casoUsoGetUsuario_data
 *
 * Verifica metodo getUserId(nome) se retorna os ids corretos para usuarios existentes e nao
 */
void DatabaseHelperImplTest::casoUsoGetUsuario()
{
    /*QVERIFY(db.getUserId("admin") == 1);
    QVERIFY(db.getUserId("breno") == 2);
    QVERIFY(db.getUserId("tiago") == 3);*/

    QFETCH(QString, nome);
    QFETCH(int, id);

    QCOMPARE(db.getUserId(nome), id);
}

void DatabaseHelperImplTest::casoUsoisAdmin_data()
{
    // ENTRADA
    QTest::addColumn<QString>("nome");
    // SAIDA
    QTest::addColumn<bool>("isAdm");

    QTest::newRow("login admin") << "admin" << true;
    QTest::newRow("login breno") << "breno" << false;
    QTest::newRow("login tiago") << "tiago" << false;
    QTest::newRow("login inexistente tiago2") << "tiago2" << false;
}

/**
 * @brief DatabaseHelperImplTest::casoUsoisAdmin
 *
 * Verifica metodo isAdmin(nome) se retona corretmante se o suario eh admin ou nao, para usaurios existentes e nao
 */
void DatabaseHelperImplTest::casoUsoisAdmin()
{
    QFETCH(QString, nome);
    QFETCH(bool, isAdm);

    QCOMPARE(db.isAdmin(nome), isAdm);
}

/**
 * @brief DatabaseHelperImplTest::casoUsoGetAllUsers
 *
 * (Necessida de banco inicial)
 * Verifica metodo getAllUsers se retorna usuarios conhecidos
 */
void DatabaseHelperImplTest::casoUsoGetAllUsers()
{
    vector<pair<QString, QString>> users = db.getAllUsers();

    qDebug() << "Size: " << users.size();
    QCOMPARE(users.size(), 3);

    for(int i = 0; i < users.size(); i++) {
        // qDebug() << users[i].first;
        // qDebug() << users[i].second;

        if (QString::compare("admin", users[i].first) == 0) {
            QCOMPARE("admin", users[i].second);
        } else if (QString::compare("breno", users[i].first) == 0) {
            QCOMPARE("keller", users[i].second);
        } else if (QString::compare("tiago", users[i].first) == 0) {
            QCOMPARE("carneiro", users[i].second);
        } else {
            QString s = "Usuario nao encontrado: |" + users[i].first + "|" + users[i].second + "|";
            QFAIL(s.toLatin1().data());
        }
    }
}

void DatabaseHelperImplTest::casoUsoInsertOperation_data()
{
    // ENTRADA
    QTest::addColumn<int>("userId");
    QTest::addColumn<double>("v1");
    QTest::addColumn<QString>("operacao");
    QTest::addColumn<double>("v2");
    QTest::addColumn<double>("resultado");
    // SAIDA
    QTest::addColumn<bool>("isOk");

    // admin 2+ 1-
    QTest::newRow("user 1 adicao 1 2") << 1 << 1.0 << "Adição" << 1.0 << 2.0 << true;
    QTest::newRow("user 1 adicao 1 2 Repetida") << 1 << 1.0 << "Adição" << 1.0 << 2.0 << true;
    QTest::newRow("user 1 subtracao 1 0") << 1 << 1.0 << "Subtração" << 1.0 << 0.0 << true;

    // breno 1/
    QTest::newRow("user 2 div 1 / 2 = 0.5") << 2 << 1.0 << "Divisão" << 2.0 << 0.5 << true;

    // tiago 1+ 1- 1/ 1*
    QTest::newRow("user 3 mult 1 * 1 = 1") << 3 << 1.0 << "Multiplicação" << 1.0 << 1.0 << true;
    QTest::newRow("user 3 adicao 1 + 1 = 2") << 3 << 1.0 << "Adição" << 1.0 << 2.0 << true;
    QTest::newRow("user 3 sub 1 - 1 = 0") << 3 << 1.0 << "Subtração" << 1.0 << 0.0 << true;
    QTest::newRow("user 3 div 1 / 1 = 1") << 3 << 1.0 << "Divisão" << 1.0 << 1.0 << true;

    // user 0 1*
    QTest::newRow("user 0 (inexistente) mult 1 * 1 = 1") << 0 << 1.0 << "Multiplicação" << 1.0 << 1.0 << true;
}

/**
 * @brief DatabaseHelperImplTest::casoUsoInsertOperation
 *
 * Verifica metodo insertOperation, se eh adicionado
 */
void DatabaseHelperImplTest::casoUsoInsertOperation()
{
    QFETCH(int, userId);
    QFETCH(double, v1);
    QFETCH(QString, operacao);
    QFETCH(double, v2);
    QFETCH(double, resultado);
    QFETCH(bool, isOk);

    QCOMPARE(db.insertOperation(userId, v1, operacao, v2, resultado), isOk);
}

/**
 * @brief DatabaseHelperImplTest::casoUsoGetOperationsByUser
 *
 * (Necessida de banco inicial)
 * (Depende dos inserts acima)
 * Verifica getOperationsByUser se valores estao coerentes com o numero de inserts feitos no banco inicial
 *
 */
void DatabaseHelperImplTest::casoUsoGetOperationsByUser()
{
    vector<pair<QString, int>> operations = db.getOperationsByUser("tiago");
    QCOMPARE(operations.size(), 4); // usuario 3 tiago, realizou uma operacao de cada

    operations = db.getOperationsByUser("admin");

    for(int i = 0; i < operations.size(); i++) {
        // qDebug() << users[i].first;
        // qDebug() << users[i].second;

        if (QString::compare("Adição", operations[i].first) == 0) {
            QCOMPARE(2, operations[i].second);
        } else if (QString::compare("Divisão", operations[i].first) == 0) {
            QCOMPARE(0, operations[i].second);
        } else if (QString::compare("Multiplicação", operations[i].first) == 0) {
            QCOMPARE(0, operations[i].second);
        } else if (QString::compare("Subtração", operations[i].first) == 0) {
            QCOMPARE(1, operations[i].second);
        } else {
            QString s = "Tipo nao encontrado: |" + operations[i].first + "|" + operations[i].second + "|";
            QFAIL(s.toLatin1().data());
        }
    }
}


/**
 * @brief DatabaseHelperImplTest::casoUsoGetOperationsByUser
 *
 * (Necessida de banco inicial)
 * (Depende dos inserts acima)
 * Verifica getAllOperations se valores estao coerentes com o numero de inserts feitos no banco inicial
 *
 */
void DatabaseHelperImplTest::casoUsoGetAllOperations()
{
    vector<pair<QString, int>> operations = db.getAllOperations();
    QCOMPARE(operations.size(), 4);

    for(int i = 0; i < operations.size(); i++) {
        // qDebug() << users[i].first;
        // qDebug() << users[i].second;

        if (QString::compare("Adição", operations[i].first) == 0) {
            QCOMPARE(3, operations[i].second);
        } else if (QString::compare("Divisão", operations[i].first) == 0) {
            QCOMPARE(2, operations[i].second);
        } else if (QString::compare("Multiplicação", operations[i].first) == 0) {
            QCOMPARE(2, operations[i].second);
        } else if (QString::compare("Subtração", operations[i].first) == 0) {
            QCOMPARE(2, operations[i].second);
        } else {
            QString s = "Tipo nao encontrado: |" + operations[i].first + "|" + operations[i].second + "|";
            QFAIL(s.toLatin1().data());
        }
    }
}

QTEST_APPLESS_MAIN(DatabaseHelperImplTest)
//#include "databasehelperimplTest.moc"
