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
        // Throw error
    }

    QSqlQuery selectQuery("SELECT id FROM users WHERE login = '" + username + "'", sqlDatabase);
    selectQuery.next();
    int userId = selectQuery.value(0).toInt();

    sqlDatabase.close();

    return userId;
}

bool DatabaseHelperImpl::insertOperation(int userId, double v1, QString operacao, double v2, double resultado){
    setupDatabase();

    if(!sqlDatabase.open()){
        // Throw error
    }

    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO operations (user_id, operando1, operador, operando2, resultado) "
                        "VALUES (:user, :par1, :op, :par2, :resultado)");
    insertQuery.bindValue(":user", userId);
    insertQuery.bindValue(":par1", v1);
    insertQuery.bindValue(":op", operacao);
    insertQuery.bindValue(":par2", v2);
    insertQuery.bindValue(":resultado", resultado);
    bool b = insertQuery.exec();

    sqlDatabase.close();

    return b;
}

vector<pair<QString, QString>> DatabaseHelperImpl::getUsers(){
    setupDatabase();

    if(!sqlDatabase.open()){
        // Throw error
    }

    vector<pair<QString, QString> > users;
    QSqlQuery search("SELECT login, senha FROM users", sqlDatabase);
    while (search.next()) {
        pair<QString, QString> userData;

        QString username = search.value(0).toString();
        QString password = search.value(1).toString();

        userData = make_pair(username, password);
        users.push_back(userData);
    }

    sqlDatabase.close();
    return users; // Retorno local, conferir
}

vector<pair<QString, int>> DatabaseHelperImpl::getOperationsByUser(QString username){
    setupDatabase();

    if(!sqlDatabase.open()){
        // Throw error
    }

    vector<pair<QString, int>> operationsByUser;
    QSqlQuery search("SELECT operador, count(*) as Frequencia FROM users as u, operations as op "
                     "WHERE op.user_id = u.id AND u.login = '" + username + "' GROUP BY operador", sqlDatabase);
    while (search.next()) {
        pair<QString, int> opData;

        QString operacao = search.value(0).toString();
        long qtd = search.value(1).toInt();

        opData = make_pair(operacao, qtd);
        operationsByUser.push_back(opData);
    }

    sqlDatabase.close();
    return operationsByUser; // Retorno local, conferir
}

vector<pair<QString, int>> DatabaseHelperImpl::getOperations(){
    setupDatabase();

    if(!sqlDatabase.open()){
        // Throw error
    }

    vector<pair<QString, int>> operations;
    QSqlQuery search("SELECT operador, count(*) as Frequencia FROM operations GROUP BY operador", sqlDatabase);
    while (search.next()) {
        pair<QString, int> opData;

        QString operacao = search.value(0).toString();
        long qtd = search.value(1).toInt();

        opData = make_pair(operacao, qtd);
        operations.push_back(opData);
    }

    sqlDatabase.close();
    return operations; // Retorno local, conferir
}

bool DatabaseHelperImpl::isAdmin(QString username){
    setupDatabase();

    if(!sqlDatabase.open()){
        // Throw error
    }

    QSqlQuery search("SELECT adminLevel FROM users WHERE login ='" + username + "'", sqlDatabase);
    search.next();
    bool adminLevel = search.value(0).toBool();

    sqlDatabase.close();
    return adminLevel;
}
