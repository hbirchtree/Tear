#include "teartcpsocket.h"
TearTCPSocket::TearTCPSocket(QObject *parent, QHostAddress host, quint16 port) : QObject(parent)
{
    QTcpSocket* socket = new QTcpSocket(this);
    initSocket(socket);
    predef_host = host;
    predef_port = port;
}

TearTCPSocket::TearTCPSocket(QObject *parent, QTcpSocket *socket) :
    QObject(parent)
{
    initSocket(socket);
}

QAbstractSocket::SocketState TearTCPSocket::getSocketState() const
{
    return sock->state();
}

QHostAddress TearTCPSocket::getHostAddress() const
{
    return sock->peerAddress();
}

quint16 TearTCPSocket::getLocalPort() const
{
    return sock->localPort();
}

quint16 TearTCPSocket::getHostPort() const
{
    return sock->peerPort();
}

QString TearTCPSocket::getHostName() const
{
    //May cause a hang!
    return sock->peerName();
}

void TearTCPSocket::sendData(QByteArray *data)
{
    quint32 s = (quint32)data->size();
    qDebug() << "Size:" << s;
    QByteArray s_buf;
    QDataStream s_str(&s_buf,QIODevice::WriteOnly);
    s_str << s;
    if(sock->write(s_buf)<0){
        qDebug("Socket failed to transfer size data");
        return;
    }
    if(sock->write(*data)<0){
        qDebug("Socket failed to transfer packet");
        return;
    }
    if(!sock->waitForBytesWritten())
        qDebug("Socket failed to write all bytes");
    delete data;
}

void TearTCPSocket::socketConnect()
{
    sock->connectToHost(predef_host,predef_port);
}

void TearTCPSocket::socketDisconnect()
{
    sock->disconnectFromHost();
}

void TearTCPSocket::handleError(QAbstractSocket::SocketError err)
{
    Q_UNUSED(err);
    qDebug("Socket error: %s",sock->errorString().toStdString().c_str());
}

void TearTCPSocket::initSocket(QTcpSocket *socket)
{
    connect(socket,&QTcpSocket::connected,[=](){
        connectionChanged(QTcpSocket::ConnectedState);
    });
    connect(socket,&QTcpSocket::disconnected,[=](){
        connectionChanged(QTcpSocket::UnconnectedState);
        this->deleteLater();
    });
    connect(socket,&QTcpSocket::aboutToClose,[=](){
        emit socketClosing();
    });
    connect(socket,&QTcpSocket::readyRead,[=](){
        while(sock->bytesAvailable()>0){

            packet_buffer.append(sock->readAll());

            while((packet_size == 0&&
                   packet_buffer.size()>=sizeof(quint32))||
                  (packet_size>0&&
                   packet_buffer.size()>=packet_size)){
                if(packet_buffer.size()>=sizeof(quint32)&&packet_size==0){
                    QByteArray s_buf(packet_buffer.mid(0,sizeof(quint32)));
                    QDataStream s_str(&s_buf,QIODevice::ReadOnly);
                    s_str >> packet_size;
                    packet_buffer = packet_buffer.remove(0,sizeof(quint32));
                    if(packet_size==0)
                        qDebug("Socket received zero-sized package");
                }

                if(packet_size>0&&
                        packet_buffer.size()>=packet_size){
                    QByteArray* packet = new QByteArray(packet_buffer.mid(0,packet_size));
                    packet_buffer = packet_buffer.remove(0,packet_size);
                    packet_size = 0;
                    packetReceived(packet);
                }
            }
        }
    });
    connect(socket,SIGNAL(error(QAbstractSocket::SocketError)),SLOT(handleError(QAbstractSocket::SocketError)));
    sock = socket;
}

