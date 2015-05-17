#ifndef TEARPAINTER
#define TEARPAINTER

#include <QQuickPaintedItem>
#include <QPainter>
#include "networking/teartcpsocket.h"
class TearPainter : public QQuickPaintedItem {

    Q_OBJECT

public:
    TearPainter(QQuickItem* parent = 0) : QQuickPaintedItem(parent){}

    void paint(QPainter *painter){
        painter->drawImage(QRect(0,0,this->width(),this->height()),drawable,QRect(0,0,drawable.width(),drawable.height()));
    }

public slots:
    void socketConnect(QString host, int port){
        if(sock)
            sock->deleteLater();
        sock = new TearTCPSocket(this,QHostAddress(host),port);
        connect(sock,&TearTCPSocket::packetReceived,[=](QByteArray* data){
            QByteArray uc = qUncompress(*data);
            QDataStream ser(&uc,QIODevice::ReadOnly);
            ser >> drawable;
            update();
        });
        sock->socketConnect();
    }
    void socketDisconnect(){
        sock->deleteLater();
        sock = nullptr;
    }

private:
    TearTCPSocket* sock = nullptr;
    QImage drawable;
};

#endif // TEARPAINTER

