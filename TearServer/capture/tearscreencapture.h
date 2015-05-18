#ifndef TEARSCREENCAPTURE_H
#define TEARSCREENCAPTURE_H

#include "common.h"
#include <QTimer>
#include <QScreen>
#include <QGuiApplication>
#include <QImage>
#include <QPixmap>
#include <QDataStream>
#include <QBuffer>
#include <QEventLoop>

class TearScreenCapture : public QObject
{
    Q_OBJECT
public:
    TearScreenCapture(QObject *parent);
    ~TearScreenCapture();

private:
    QScreen* target;
    QTimer * timeywimey;

private slots:
    void capture();

signals:
    void newFrame(QByteArray* frame);

public slots:
    void run();
    void start();
    void stop();
};

#endif // TEARSCREENCAPTURE_H
