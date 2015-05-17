#include "tearimageprovider.h"

TearImageProvider::TearImageProvider(QString host, int port) :
    QQuickImageProvider(QQuickImageProvider::Image)
{
    sock = new TearTCPSocket(0,QHostAddress(host),port);
    QObject::connect(sock,&TearTCPSocket::packetReceived,[=](QByteArray* data){
        QByteArray uc = qUncompress(*data);
        QDataStream ser(&uc,QIODevice::ReadOnly);
        QImage img;
        ser >> img;
        latest = img;
    });
    sock->socketConnect();
    qDebug("Status: %s",sock->getHostAddress().toString().toStdString().c_str());
}

TearImageProvider::~TearImageProvider()
{
    delete sock;
}



QImage TearImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    size->setWidth(latest.width());
    size->setHeight(latest.height());
    return latest.scaled(requestedSize);
}
