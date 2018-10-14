#include "databasehelperimpl.h"

#include <QSqlQuery>
#include <QVariant>

DatabaseHelperImpl::DatabaseHelperImpl(){}

DatabaseHelperImpl::~DatabaseHelperImpl(){}

void DatabaseHelperImpl::setupDatabase(){
    sqlDatabase = QSqlDatabase::addDatabase("QSQLITE");
    sqlDatabase.setDatabaseName("calc_example.sqlite");
}

int DatabaseHelperImpl::getUserId(QString username){
    setupDatabase();
    if(!sqlDatabase.open()){
        throw "Não foi possivel se conectar ao banco de dados";
    }

    QSqlQuery select("SELECT id FROM users WHERE login = '" + username + "'", sqlDatabase);
    select.next();
    int userId = select.value(0).toInt();

    sqlDatabase.close();

    return userId;
}

bool DatabaseHelperImpl::insertOperation(int userId, double v1, QString operacao, double v2, double resultado){
    setupDatabase();

    if(!sqlDatabase.open()){
        throw "Não foi possivel se conectar ao banco de dados";
    }

    QSqlQuery insert;
    insert.prepare("INSERT INTO operations (user_id, operando1, operador, operando2, resultado) "
                        "VALUES (:user, :par1, :op, :par2, :resultado)");
    insert.bindValue(":user", userId);
    insert.bindValue(":par1", v1);
    insert.bindValue(":op", operacao);
    insert.bindValue(":par2", v2);
    insert.bindValue(":resultado", resultado);
    bool b = insert.exec();

    sqlDatabase.close();

    return b;
}

vector<pair<QString, QString>> DatabaseHelperImpl::getAllUsers(){
    setupDatabase();

    if(!sqlDatabase.open()){
        throw "Não foi possivel se conectar ao banco de dados";
    }

    vector<pair<QString, QString> > users;
    QSqlQuery select("SELECT login, senha FROM users", sqlDatabase);
    while (select.next()) {
        pair<QString, QString> userData;

        QString username = select.value(0).toString();
        QString password = select.value(1).toString();

        userData = make_pair(username, password);
        users.push_back(userData);
    }

    sqlDatabase.close();
    return users;
}

vector<pair<QString, int>> DatabaseHelperImpl::getOperationsByUser(QString username){
    setupDatabase();

    if(!sqlDatabase.open()){
        throw "Não foi possivel se conectar ao banco de dados";
    }

    vector<pair<QString, int>> operationsByUser;
    QSqlQuery select("SELECT operador, count(*) as Frequencia FROM users as u, operations as op "
                     "WHERE op.user_id = u.id AND u.login = '" + username + "' GROUP BY operador", sqlDatabase);
    while (select.next()) {
        pair<QString, int> opData;

        QString operacao = select.value(0).toString();
        long value = select.value(1).toInt();

        opData = make_pair(operacao, value);
        operationsByUser.push_back(opData);
    }

    sqlDatabase.close();
    return operationsByUser;
}

vector<pair<QString, int>> DatabaseHelperImpl::getAllOperations(){
    setupDatabase();

    if(!sqlDatabase.open()){
        throw "Não foi possivel se conectar ao banco de dados";
    }

    vector<pair<QString, int>> operations;
    QSqlQuery select("SELECT operador, count(*) as Frequencia FROM operations GROUP BY operador", sqlDatabase);
    while (select.next()) {
        pair<QString, int> opData;

        QString operacao = select.value(0).toString();
        long value = select.value(1).toInt();

        opData = make_pair(operacao, value);
        operations.push_back(opData);
    }

    sqlDatabase.close();
    return operations;
}

bool DatabaseHelperImpl::isAdmin(QString username){
    setupDatabase();

    if(!sqlDatabase.open()){
        throw "Não foi possivel se conectar ao banco de dados";
    }

    QSqlQuery select("SELECT adminLevel FROM users WHERE login ='" + username + "'", sqlDatabase);
    select.next();
    bool adminLevel = select.value(0).toBool();

    sqlDatabase.close();
    return adminLevel;
}
