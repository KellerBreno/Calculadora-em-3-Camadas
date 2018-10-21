#include "../dialog.h"

#include <QtTest/QtTest>
#include <QtDebug>
#include <QLabel>
#include <QHostInfo>
#include <QPushButton>

class DialogTest : public QObject
{
    Q_OBJECT

public:
    DialogTest();
    ~DialogTest();

private slots:
    void casoUsoPrincipal_data();
    void casoUsoPrincipal();

private:
    Dialog d;
};
