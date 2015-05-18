#include <QApplication>
#include <QQmlApplicationEngine>
#include "qml/tearpainter.h"
#include "qml/tearinput.h"
#include "qml/eventcapture.h"
#include <QtQml/QtQml>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //Captures keys, mouse and scrolling
    qmlRegisterType<TearInputField>("TearProvider",1,0,"TearInputArea");
    //Sends signals to server
    qmlRegisterType<TearInput>("TearProvider",1,0,"TearInputSocket");
    //Receives and draws what the server sends
    qmlRegisterType<TearPainter>("TearProvider",1,0,"TearPainter");
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
