#include <QApplication>
#include <QQmlApplicationEngine>
#include "qml/tearpainter.h"
#include <QtQml/QtQml>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<TearPainter>("TearProvider",1,0,"TearPainter");
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
