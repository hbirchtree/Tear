#ifndef TEARTCPSERVER_H
#define TEARTCPSERVER_H

#include "common.h"
#include "teartcpsocket.h"

class TearTCPServer : public QObject
{
    Q_OBJECT
public:
    TearTCPServer(QObject *parent,QNetworkInterface interface,quint16 port);

    bool isValid();

signals:
    void newConnection(TearTCPSocket* socket);

public slots:

private:
    bool b_valid = false;

    QTcpServer* server;
};

#endif // TEARTCPSERVER_H
