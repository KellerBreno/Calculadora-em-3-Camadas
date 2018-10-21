#include "../databasehelperimpl.h"

#include <QtTest/QtTest>
#include <QtDebug>

class DatabaseHelperImplTest : public QObject
{
    Q_OBJECT

public:
    DatabaseHelperImplTest();
    ~DatabaseHelperImplTest();

private slots:
    void casoUsoConectaBanco();

    void casoUsoGetUsuario_data();
    void casoUsoGetUsuario();

    void casoUsoisAdmin_data();
    void casoUsoisAdmin();

    void casoUsoGetAllUsers();

    void casoUsoInsertOperation_data();
    void casoUsoInsertOperation();

    void casoUsoGetOperationsByUser();

    void casoUsoGetAllOperations();

private:
    DatabaseHelperImpl db;
};
