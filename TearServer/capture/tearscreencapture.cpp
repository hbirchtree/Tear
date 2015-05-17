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

    //When the timer is stopped, some frames are redundant.
    //We delete these when there are no receivers for the newFrame() signal
    //In early releases, this was a blatant memory leak as packets
    // are only disposed of *if they are sent* normally.
    if( receivers(SIGNAL(newFrame(QByteArray*))) > 0)
        newFrame(frame);
    else
        delete frame;
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
}

void TearScreenCapture::start()
{
    timeywimey->start();
}

void TearScreenCapture::stop()
{
    timeywimey->stop();
}

