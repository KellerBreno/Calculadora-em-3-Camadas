/*!
 * \file networkmanager.h
 * Arquivo contendo a Declaração da Interface NetworkManager
 */

#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QString>
#include <QObject>
#include <QJsonObject>

#include <data/adminuser.h>
#include <data/basicuser.h>

/*!
 * \class NetworkManager
 * \brief Classe para gerenciar comunicações entre a gui e o server pela rede
 */
class NetworkManager{
private:
    /*!
     * \brief Instancia única da classe
     */
    static NetworkManager* instance;
public:
    /*!
     * \brief Este método retorna uma instancia de NetworkManager
     * \return Instancia de NetworkManager*
     */
    static NetworkManager* getInstance();

    /*!
     * \brief Método para configurar o NetworkManager
     * \param ip Ip do Servidor
     * \param port Porta do Servidor
     */
    virtual void configure(QString ip, quint16 port) = 0;

    /*!
     * \brief Método para realizar um login
     * \param username Nome do usuário
     * \param password Senha do usuário
     */
    virtual void login(BasicUser *basicUser) = 0;

    /*!
     * \brief Método para realizar operações matematicas
     * \param username Nome do usuário
     * \param factor1 Primeiro fator da operação
     * \param factor2 Segundo fator da operação
     * \param opCode Código da operação
     */
    virtual void doOperation(BasicUser *basicUser, double factor1, double factor2, int opCode) = 0;

    /*!
     * \brief Método para recuperar o relatorio de operações do usuário
     * \param username Nome do usuário a ser gerado o relatorio
     * \sa NetworkManager::reportAllUsers()
     */
    virtual void reportByUser(BasicUser *basicUser) = 0;

    /*!
     * \brief Método para recuperar o relatorio de operações de todos os usuários
     * \param username Nome do usuário solicitando
     * \sa NetworkManager::reportByUser()
     */
    virtual void reportAllUsers(AdminUser *adminUser) = 0;

    /*!
     * \brief Retorna um QObject referente a NetworkManager
     * \return QObject correspondente
     */
    virtual QObject* getQObject() = 0;

    /*!
     * \brief Método que recebe como parametro o Json correspondente da resposta
     * \param jsonObject Resposta recebida do servidor
     */
    virtual void messageReceive(QJsonObject jsonObject) = 0;
};

#endif // NETWORKMANAGER_H
