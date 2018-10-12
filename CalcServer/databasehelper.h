#ifndef DATABASEHELPER_H
#define DATABASEHELPER_H

#include <QString>

#include <utility>
#include <vector>

using namespace std;

class DatabaseHelper{
public:
    virtual int getUserId(QString username) = 0;
    virtual bool insertOperation(int userId, double v1, QString operacao, double v2, double resultado) = 0;
    virtual vector<pair<QString, QString>> getUsers() = 0;
    virtual vector<pair<QString, int>> getOperationsByUser(QString username) = 0;
    virtual vector<pair<QString, int>> getOperations() = 0;
};

#endif // DATABASEHELPER_H
