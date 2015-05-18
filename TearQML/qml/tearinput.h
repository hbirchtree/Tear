#ifndef TEARINPUT
#define TEARINPUT

#include "common.h"
#include <QVariantMap>
#include <QRect>
#include <QVariantList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "networking/teartcpsocket.h"
#include "streamer-shared.h"
class TearInput : public QObject {

    Q_OBJECT
public slots:
    void sendInput(int type, int val1, int val2){
        if(!connected)
            return;
        QJsonObject d;
        QJsonArray i;
        i << type << val1 << val2;
        d.insert("t",StreamerSharedProperties::SD_InputSignal);
        d.insert("v",i);
        QJsonDocument doc;
        doc.setObject(d);
        QByteArray* data = new QByteArray(doc.toJson());
        sock->sendData(data);
    }

    void socketConnect(QString host,int port){
//        if(sock)
//            sock->deleteLater();
        sock = new TearTCPSocket(this,QHostAddress(host),port);
        connect(sock,&TearTCPSocket::packetReceived,[=](QByteArray* data){
            QVariantMap doc = QJsonDocument::fromJson(*data).object().toVariantMap();
            delete data;
            switch(doc.value("t").toInt()){
            case StreamerSharedProperties::SD_CommandSignal:
                processCommand(doc);
                break;
            }
        });
        connect(sock,&TearTCPSocket::connectionChanged,[=](QAbstractSocket::SocketState s){
            switch(s){
            case QAbstractSocket::ConnectedState:
                socketConnectivityChanged(true);
                connected = true;
                announceConnected();
                break;
            case QAbstractSocket::UnconnectedState:
                socketConnectivityChanged(false);
                connected = false;
                announceDisconnected();
                break;
            default:
                break;
            }
        });
        sock->socketConnect();
    }
    void socketDisconnect(){
        if(sock){
            sock->socketDisconnect();
            sock->deleteLater();
            sock = nullptr;
        }
    }

signals:
    void socketConnectivityChanged(bool connected);
    void announceAVSource(QString host,int port);
    void announceScreenDimensions(int x,int y,int w,int h);
    void announceConnected();
    void announceDisconnected();

private slots:
    void processCommand(const QVariantMap &cmd){
        int c(cmd.value("c").toInt());
        if(c&(int)StreamCmdFlags::AvDescriptor){
            announceAVSource(cmd.value("h").toString(),cmd.value("p").toInt());
        }
        if(c&(int)StreamCmdFlags::ScreenDimensions){
            QVariantList dim = cmd.value("d").toList();
            QRect d;
            for(int i=0;i<dim.size();i++)
                switch(i){
                case 0:
                    d.setX(dim.at(i).toInt());
                    break;
                case 1:
                    d.setY(dim.at(i).toInt());
                    break;
                case 2:
                    d.setWidth(dim.at(i).toInt());
                    break;
                case 3:
                    d.setHeight(dim.at(i).toInt());
                    break;
                }
            announceScreenDimensions(d.x(),d.y(),
                                     d.width(),d.height());
        }
    }

private:
    bool connected = false;
    TearTCPSocket* sock = nullptr;
};

#endif // TEARINPUT

