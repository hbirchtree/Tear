#include "tearinputhandler.h"

TearInputHandler::TearInputHandler(QObject *parent) : QObject(parent)
{

}

InputHandlerObjectInterface *TearInputHandler::loadInputHandler(QString file, QObject *parent)
{
    QPluginLoader libhandle(file,parent);
    InputHandlerObjectInterface* handler = nullptr;
    if(libhandle.load()&&libhandle.isLoaded()){
        handler = qobject_cast<InputHandlerObjectInterface*>(libhandle.instance());
        handler->testFunc();
    }else{
        qDebug("Failed to load library: %s",file.toStdString().c_str());
    }
    return handler;
}

void TearInputHandler::addHandlerMapping(int type,InputHandlerObjectInterface *handler)
{
    connect(handler,SIGNAL(pass__input(qint16,qint64,qint64)),SLOT(interpretSignalDirect(qint16,qint64,qint64)));
    handlerMappings.insert(type,handler);
}

void TearInputHandler::setKeyboardMapping(InputHandlerObjectInterface *handler)
{
    addHandlerMapping(QEvent::KeyPress,handler);
    addHandlerMapping(QEvent::KeyRelease,handler);
}

void TearInputHandler::setMouseMapping(InputHandlerObjectInterface *handler)
{
    addHandlerMapping(QEvent::MouseMove,handler);
    addHandlerMapping(QEvent::MouseButtonRelease,handler);
    addHandlerMapping(QEvent::MouseButtonPress,handler);
    addHandlerMapping(QEvent::TabletMove,handler);
    addHandlerMapping(QEvent::Wheel,handler);
}

//If we ever want a socket purely for input
void TearInputHandler::interpretSignal(QByteArray *data)
{
    QJsonDocument doc;
    doc = QJsonDocument::fromJson(*data);
    QVariantList t = doc.array().toVariantList();
    if(t.size()<3)
        qDebug() << "Bad input:" << *data;

    interpretSignalDirect(t.at(0).toInt(),t.at(1).toInt(),t.at(2).toInt());
}

void TearInputHandler::interpretSignalDirect(qint16 t, qint64 v1, qint64 v2)
{
    if(handlerMappings.contains(t))
        handlerMappings.value(t)->take__input(t,v1,v2);
}
