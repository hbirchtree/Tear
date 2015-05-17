#include "tearclienthandler.h"

TearClientHandler::TearClientHandler(QObject *parent) : QObject(parent)
{

}

QByteArray *TearClientHandler::generateWelcomePacket()
{
    QDesktopWidget dw;
    int display = dw.primaryScreen();

    QJsonObject data;
    QJsonArray dims;
    dims << dw.screenGeometry(display).x() <<
            dw.screenGeometry(display).y() <<
            dw.screenGeometry(display).width() <<
            dw.screenGeometry(display).height();
    data.insert("t",StreamerSharedProperties::SD_CommandSignal);
    data.insert("screen-dims",dims);

    QJsonDocument doc;
    doc.setObject(data);

    return new QByteArray(doc.toJson());
}
