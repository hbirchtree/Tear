#include "tearscreencapture.h"

TearScreenCapture::TearScreenCapture(QObject *parent) : QObject(parent)
{

}

TearScreenCapture::~TearScreenCapture()
{
    delete timeywimey;
}

void TearScreenCapture::capture()
{
    //Remember to delete the frame!
    QImage vp = target->grabWindow(0,0,0,1920,1200).toImage();

    QByteArray frame_f;

    QDataStream ser(&frame_f,QIODevice::WriteOnly);
    ser << vp;

    QByteArray *frame = new QByteArray(qCompress(frame_f,5));

    newFrame(frame);
}

void TearScreenCapture::run()
{
    //We create the object and connect it in this thread
    //All connections to this object should be queued, by the way.
    timeywimey = new QTimer();
    timeywimey->setInterval(0);
    connect(timeywimey,SIGNAL(timeout()),this,SLOT(capture()));
    target = QGuiApplication::primaryScreen();

    QEventLoop l;
    l.exec();
    qDebug() << "A/V thread quitting";
}

void TearScreenCapture::start()
{
    qDebug("Timer Thread: %p, %p",this->thread(),timeywimey->thread());
    timeywimey->start();
}

void TearScreenCapture::stop()
{
    timeywimey->stop();
}

