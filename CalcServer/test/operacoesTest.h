#include "../workerthread.h"
#include "../databasehelperimpl.h"

#include <QtTest/QtTest>
#include <QtDebug>
#include <QJsonObject>

class OperacoesTest : public QObject
{
    Q_OBJECT

public:
    OperacoesTest();
    ~OperacoesTest();

private slots:
    void casoUsoOperacoesUsuario_data();
    void casoUsoOperacoesUsuario();

    void casoUsoRelatorios_data();
    void casoUsoRelatorios();

    void casoUsoInserts_data();
    void casoUsoInserts();

private:
    WorkerThread *workertThread;

    QJsonObject getAllOperation(QString user);
    QJsonObject getAllOperationUser(QString use);
    QJsonObject loginUser(QString user, QString passwd);
    QJsonObject insert(QString user, double v1, int opCode, double v2);

    int contaOperacoes(QJsonObject json);
    int contaOperacoesOp(QJsonObject json, QString op);
};
