#ifndef TEARCLIENTHANDLER_H
#define TEARCLIENTHANDLER_H

#include "common.h"
#include "streamer-shared.h"
#include <QJsonObject>
#include <QSize>
#include <QRect>
#include <QDesktopWidget>
#include <QJsonDocument>
#include <QJsonArray>

class TearClientHandler : public QObject
{
    Q_OBJECT
public:
    TearClientHandler(QObject *parent);

    static QByteArray *generateWelcomePacket(QString currentHost, int currentAvPort);

signals:

public slots:
};

#endif // TEARCLIENTHANDLER_H
