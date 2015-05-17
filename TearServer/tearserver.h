#ifndef TEARSERVER_H
#define TEARSERVER_H

#include <QWidget>
#include <QVariantMap>
#include "networking/tearnetworkmanager.h"
#include "streamer-shared.h"
#include "handlers/tearinputhandler.h"
#include "handlers/tearclienthandler.h"
#include "capture/tearscreencapture.h"
#include <QJsonDocument>
#include <QThread>

namespace Ui {
class TearServer;
}

class TearServer : public QWidget
{
    Q_OBJECT

public:
    TearServer(QWidget *parent = 0);

    static void defaultMessageHandler(QtMsgType t, const QMessageLogContext &context, const QString &msg);
    ~TearServer();

signals:
    void startScreencap();
    void stopScreencap();

public slots:
    void appendLog(const QString &message);

private slots:
    void on_disconnectBtn_clicked();

private:
    void initInputHandler(QVariantMap data);

    quint16 inputPort = 46600;
    quint16 avPort = 46601;

    TearScreenCapture* screencap;
    TearInputHandler* inputHandler;
    TearTCPSocket* test = nullptr;
    TearNetworkManager* netman;
    Ui::TearServer *ui;
};

#endif // TEARSERVER_H
