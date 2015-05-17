#include "teartcpserver.h"

TearTCPServer::TearTCPServer(QObject *parent,QNetworkInterface interface,quint16 port) : QObject(parent)
{
    server = new QTcpServer(this);

    QHostAddress listen;
    for(QNetworkAddressEntry e : interface.addressEntries())
        if(e.ip()!=QHostAddress::AnyIPv6){
            listen = e.ip();
            break;
        }
    if(!server->listen(listen,port)){
        qWarning("Failed to set up listener on: %s, port %i",
               interface.humanReadableName().toStdString().c_str(),port);
        b_valid = false;
        return;
    }
    qDebug("Now listening on: %s, port %i",
           interface.humanReadableName().toStdString().c_str(),port);
    connect(server,&QTcpServer::newConnection,[=](){
        QTcpSocket* sock = server->nextPendingConnection();
        TearTCPSocket* tsock = new TearTCPSocket(this,sock);
        newConnection(tsock);
    });
    connect(server,&QTcpServer::acceptError,[=](QAbstractSocket::SocketError err){
        qDebug("Socket error in instance %p: %s",server,server->errorString().toStdString().c_str());
    });
}

bool TearTCPServer::isValid()
{
    return b_valid;
}

