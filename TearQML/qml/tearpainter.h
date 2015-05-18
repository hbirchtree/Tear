#ifndef TEARPAINTER
#define TEARPAINTER

#include "common.h"
#include <QQuickPaintedItem>
#include <QPainter>
#include <QBuffer>
#include "networking/teartcpsocket.h"
class TearPainter : public QQuickPaintedItem {
    Q_PROPERTY(QRect targetArea READ targetArea WRITE setTargetArea NOTIFY targetAreaChanged)

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
        setTargetArea(target);
        painter->drawImage(target,drawable,source);
    }
    QRect targetArea() const{
        return target;
    }

public slots:
    void socketConnect(QString host, int port){
        if(sock)
            sock->deleteLater();
        sock = new TearTCPSocket(this,QHostAddress(host),port);
        connect(sock,&TearTCPSocket::packetReceived,[=](QByteArray* data){
//            QByteArray uc = qUncompress(*data);
//            QDataStream ser(&uc,QIODevice::ReadOnly);
//            ser >> drawable;
            QBuffer buff;
            buff.setData(qUncompress(*data));
            delete data;
            drawable.load(&buff,"JPEG");

            update();
        });
        sock->socketConnect();
    }
    void socketDisconnect(){
        sock->deleteLater();
        sock = nullptr;
    }

    void setTargetArea(QRect targetArea)
    {
        if (m_targetArea == targetArea)
            return;

        m_targetArea = targetArea;
        emit targetAreaChanged(targetArea);
    }

signals:
    void targetAreaChanged(QRect targetArea);

private:
    QRect target;
    TearTCPSocket* sock = nullptr;
    QImage drawable;
    QRect m_targetArea;
};

#endif // TEARPAINTER

