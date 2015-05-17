#ifndef TEARVIDEOSOURCE
#define TEARVIDEOSOURCE

#include "networking/teartcpsocket.h"
#include <QObject>
#include <QAbstractVideoSurface>
#include <QVideoFrame>
#include <QHostAddress>
#include <QDataStream>
#include <QImage>
class TearVideoSource : public QObject {
    Q_OBJECT
    Q_PROPERTY(QAbstractVideoSurface *videoSurface READ videoSurface WRITE setVideoSurface NOTIFY videoSurfaceChanged)
    Q_PROPERTY(bool connected READ connected)

public:
    QAbstractVideoSurface * videoSurface() const
    {
        return m_videoSurface;
    }

    bool connected() const
    {
        return m_connected;
    }

public slots:
    void socketConnect(QString host, int port){
        sock = new TearTCPSocket(this,QHostAddress(host),port);
        connect(sock,&TearTCPSocket::packetReceived,[=](QByteArray* data){
            QByteArray uc = qUncompress(*data);
            QDataStream ser(&uc,QIODevice::ReadOnly);
            QImage img;
            ser >> img;
            qDebug("Image: %ix%i",img.width(),img.height());
            QVideoFrame frame(img);
            m_videoSurface->present(frame);
        });
        sock->socketConnect();
    }
    void socketDisconnect(){
        if(sock){
            sock->socketDisconnect();
            sock = nullptr;
        }
    }

    void setVideoSurface(QAbstractVideoSurface * videoSurface)
    {
        if (m_videoSurface == videoSurface)
            return;

        m_videoSurface = videoSurface;
        emit videoSurfaceChanged(videoSurface);
    }

signals:
    void videoSurfaceChanged(QAbstractVideoSurface * videoSurface);

private:
    TearTCPSocket* sock;
    QAbstractVideoSurface * m_videoSurface;
    bool m_connected;
};

#endif // TEARVIDEOSOURCE

