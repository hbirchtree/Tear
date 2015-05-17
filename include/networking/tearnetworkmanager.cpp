#include "tearnetworkmanager.h"

TearNetworkManager::TearNetworkManager(QObject *parent) :
    QObject(parent),
    interface(QNetworkInterface::allInterfaces().first())
{

}

void TearNetworkManager::registerNewListeningPort(quint16 port)
{
    TearTCPServer* server = new TearTCPServer(this,interface,port);
    connect(server,&TearTCPServer::newConnection,[=](TearTCPSocket* socket){
        sockets.append(socket);
        newConnection(socket,socket->getHostAddress(),socket->getLocalPort());
    });
    servers.append(server);
}

void TearNetworkManager::registerNewConnection(TearTCPSocket **pointer, QHostAddress address, quint16 port)
{
    TearTCPSocket* socket = new TearTCPSocket(this,address,port);
    sockets.append(socket);
    *pointer = socket;
}
QNetworkInterface TearNetworkManager::getInterface() const
{
    return interface;
}

void TearNetworkManager::setInterface(const QNetworkInterface &value)
{
    interface = value;
}
