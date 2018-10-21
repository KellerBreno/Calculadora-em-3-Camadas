#include "dialogTest.h"

DialogTest::DialogTest()
{

}

DialogTest::~DialogTest()
{

}

void DialogTest::casoUsoPrincipal_data()
{
    // ENTRADA
    QTest::addColumn<int>("ms");
    QTest::addColumn<QString>("inicioSaida");
    QTest::addColumn<QString>("meioSaida");
    QTest::addColumn<QString>("finalSaida");
    QTest::addColumn<QPushButton*>("botaoSair");

    QTest::newRow("Server subiu com IP valido") << 500 << "O server está funcionando no\n\nIP: " << "\nPorta: " << "\n\nExecute o CalcClient agora." << d.quitButton;
}

/**
 * @brief DialogTest::casoUsoPrincipal
 *
 * Verifica se tela do server foi criada, e se possui um IP e porta validos
 */
void DialogTest::casoUsoPrincipal()
{
    QFETCH(int, ms);
    QFETCH(QString, inicioSaida);
    QFETCH(QString, meioSaida);
    QFETCH(QString, finalSaida);
    QFETCH(QPushButton*, botaoSair);

    d.show();

    QCOMPARE(d.isHidden(), false);
    QCOMPARE(d.isVisible(), true);

    //QTRY_COMPARE_WITH_TIMEOUT(!d.statusLabel->text().isEmpty(), true, ms);
    //QTRY_COMPARE_WITH_TIMEOUT(QApplication::topLevelWidgets().isEmpty(), false, ms);

    QTest::qWait(ms);
    QCOMPARE(QApplication::topLevelWidgets().isEmpty(), false);

    QString texto = d.statusLabel->text();

    QCOMPARE(texto.startsWith(inicioSaida), true);
    QCOMPARE(texto.endsWith(finalSaida), true);

    QString texto2 = texto.remove(inicioSaida);
    QString texto2porta = QString(texto2);

    QString porta = texto2porta.remove(0, texto2porta.indexOf(meioSaida) + meioSaida.size());
    porta = porta.remove(porta.indexOf(finalSaida), porta.size());

    QCOMPARE(porta.split(" ")[0].toInt() > 0, true);

    QString ip = texto2.remove(texto2.indexOf(meioSaida), texto2.size());

    QRegExp regexIPv4 = QRegExp("^([01]?\\d\\d?|2[0-4]\\d|25[0-5])\\.([01]?\\d\\d?|2[0-4]\\d|25[0-5])\\.([01]?\\d\\d?|2[0-4]\\d|25[0-5])\\.([01]?\\d\\d?|2[0-4]\\d|25[0-5])$");
    QRegExp regexIPv6 = QRegExp("(([0-9a-fA-F]{1,4}:){7,7}[0-9a-fA-F]{1,4}|([0-9a-fA-F]{1,4}:){1,7}:|([0-9a-fA-F]{1,4}:){1,6}:[0-9a-fA-F]{1,4}|([0-9a-fA-F]{1,4}:){1,5}(:[0-9a-fA-F]{1,4}){1,2}|([0-9a-fA-F]{1,4}:){1,4}(:[0-9a-fA-F]{1,4}){1,3}|([0-9a-fA-F]{1,4}:){1,3}(:[0-9a-fA-F]{1,4}){1,4}|([0-9a-fA-F]{1,4}:){1,2}(:[0-9a-fA-F]{1,4}){1,5}|[0-9a-fA-F]{1,4}:((:[0-9a-fA-F]{1,4}){1,6})|:((:[0-9a-fA-F]{1,4}){1,7}|:)|fe80:(:[0-9a-fA-F]{0,4}){0,4}%[0-9a-zA-Z]{1,}|::(ffff(:0{1,4}){0,1}:){0,1}((25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9])\.){3,3}(25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9])|([0-9a-fA-F]{1,4}:){1,4}:((25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9])\.){3,3}(25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9]))");

    if (regexIPv6.exactMatch(ip))
    {
        QCOMPARE(regexIPv4.exactMatch(ip), true);
    }
    else
    {
        QVERIFY(true); // passou para IPv6
    }

    QTest::mouseClick(botaoSair, Qt::LeftButton);
    QCOMPARE(d.isVisible(), false);
}

QTEST_MAIN(DialogTest)
//#include "dialogTest.moc"
