#ifndef TEARIMAGEPROVIDER_H
#define TEARIMAGEPROVIDER_H

#include <QQuickImageProvider>
#include <QImage>
#include <QHostAddress>
#include <QDataStream>
#include "networking/teartcpsocket.h"

class TearImageProvider : public QQuickImageProvider
{
public:
    TearImageProvider(QString host, int port);
    ~TearImageProvider();

    QImage requestImage(const QString &id, QSize* size, const QSize &requestedSize);

private:
    TearTCPSocket* sock;
    QImage latest;
};

#endif // TEARIMAGEPROVIDER_H
