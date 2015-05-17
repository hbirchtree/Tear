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
        QRect target(0,0,this->width(),this->height());
        QRect source(0,0,drawable.width(),drawable.height());
        float da = (float)this->width()/(float)this->height();//display aspect ratio
        float sa = (float)source.width()/(float)source.height();//source aspect ratio

        //We scale it to fit the screen with its original aspect ratio
        //We also center it on screen
        if(da<sa){
            target.setHeight(this->width()/sa);
            target.setWidth(this->width());
            target.setY((this->height()-target.height())/2);
        }else if(da>sa){
            target.setHeight(this->height());
            target.setWidth(this->height()*sa);
            target.setX((this->width()-target.width())/2);
        }
        painter->setRenderHints(QPainter::Antialiasing);
        painter->drawImage(target,drawable,source);
    }

public slots:
    void socketConnect(QString host, int port){
        if(sock)
            sock->deleteLater();
        sock = new TearTCPSocket(this,QHostAddress(host),port);
        connect(sock,&TearTCPSocket::packetReceived,[=](QByteArray* data){
            QByteArray uc = qUncompress(*data);
            delete data;
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

