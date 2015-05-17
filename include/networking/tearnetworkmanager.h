#ifndef TEARNETWORKMANAGER_H
#define TEARNETWORKMANAGER_H

#include "common.h"
#include "teartcpserver.h"
#include "teartcpsocket.h"
class TearNetworkManager : public QObject
{
    Q_OBJECT
public:
    TearNetworkManager(QObject *parent);

    QNetworkInterface getInterface() const;
    void setInterface(const QNetworkInterface &value);

signals:
    //Giving feedback to the GUI as well as crossing data streams
    void newConnection(TearTCPSocket* socket,QHostAddress host,quint16 port);

public slots:
    void registerNewListeningPort(quint16 port);
    //Yup. A pointer to a pointer. In a slot.
    void registerNewConnection(TearTCPSocket **pointer,QHostAddress address,quint16 port);

private:
    QNetworkInterface interface;

    QList<TearTCPServer*> servers;
    QList<TearTCPSocket*> sockets;
};

#endif // TEARNETWORKMANAGER_H
