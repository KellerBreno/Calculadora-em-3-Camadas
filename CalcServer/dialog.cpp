#include <QtWidgets>
#include <QtNetwork>

#include <stdlib.h>

#include "dialog.h"
#include "server.h"

Dialog::Dialog(QWidget *parent) : QWidget(parent){
    statusLabel = new QLabel;
    statusLabel->setWordWrap(true);
    quitButton = new QPushButton(tr("Sair"));
    quitButton->setAutoDefault(false);

    if (!server.listen()) {
        QMessageBox::critical(this, tr("CalcServer"), tr("Não foi possivel iniciar o server: %1.").arg(server.errorString()));
        close();
        return;
    }

    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();

    // Utiliza o primeiro IP que não for localhost
    for (int i = 0; i < ipAddressesList.size(); i++) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost && ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    // Se não tiver nenhum IP da rede, utiliza o de localhost
    if (ipAddress.isEmpty()){
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    }

    statusLabel->setText(tr("O server está funcionando no\n\nIP: %1\nPorta: %2\n\nExecute o CalcClient agora.")
                         .arg(ipAddress).arg(server.serverPort()));

    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(quitButton);
    buttonLayout->addStretch(1);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(statusLabel);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
    setWindowTitle(tr("CalcServer"));
}
