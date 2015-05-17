#ifndef TEARINPUTHANDLER_H
#define TEARINPUTHANDLER_H

#include "common.h"
#include <QObject>
#include <QMap>
#include <QEvent>
#include <QPluginLoader>
#include <QJsonDocument>
#include <QJsonArray>
#include <QVariantList>
#include "inputhandlerinterface.h"

class TearInputHandler : public QObject
{
    Q_OBJECT
public:
    TearInputHandler(QObject *parent);

    static InputHandlerObjectInterface* loadInputHandler(QString file,QObject* parent);

    void addHandlerMapping(int type, InputHandlerObjectInterface* handler);
    void setKeyboardMapping(InputHandlerObjectInterface* handler);
    void setMouseMapping(InputHandlerObjectInterface* handler);

public slots:
    void interpretSignal(QByteArray* data);
    void interpretSignal(qint16 t,qint64 v1,qint64 v2);

signals:

private:
    QMap<int,InputHandlerObjectInterface*> handlerMappings;
};

#endif // TEARINPUTHANDLER_H
