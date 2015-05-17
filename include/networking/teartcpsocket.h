#ifndef TEARTCPSOCKET_H
#define TEARTCPSOCKET_H

#include "common.h"

class TearTCPSocket : public QObject
{
    Q_OBJECT
public:
    TearTCPSocket(QObject *parent, QHostAddress host, quint16 port);
    TearTCPSocket(QObject *parent, QTcpSocket* socket); //For an existing socket, just to wrap it up

    QAbstractSocket::SocketState getSocketState() const;
    QHostAddress getHostAddress() const;
    quint16 getLocalPort() const;
    QHostAddress getLocalAddress() const;
    quint16 getHostPort() const;
    QString getHostName() const;

signals:
    void connectionChanged(QAbstractSocket::SocketState state);
    void packetReceived(QByteArray* data);

    void socketClosing();

public slots:
    void sendData(QByteArray* data);

    void socketConnect();
    void socketDisconnect();

private slots:
    void handleError(QAbstractSocket::SocketError err);

private:
    QHostAddress predef_host;
    quint16 predef_port;

    void initSocket(QTcpSocket* socket);

    QTcpSocket* sock;

    quint32 packet_size = 0;
    QByteArray packet_buffer;
};

#endif // TEARTCPSOCKET_H
