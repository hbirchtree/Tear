#include <QApplication>
#include <QQmlApplicationEngine>
#include "qml/tearpainter.h"
#include "qml/tearinput.h"
#include <QtQml/QtQml>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<TearInput>("TearProvider",1,0,"TearInputSocket");
    qmlRegisterType<TearPainter>("TearProvider",1,0,"TearPainter");
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
