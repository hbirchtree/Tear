TEMPLATE = app

QT += qml quick widgets multimedia sensors

CONFIG += c++11

SOURCES += main.cpp \
    ../include/networking/teartcpsocket.cpp
HEADERS += \
    ../include/networking/teartcpsocket.h \
    qml/tearvideosource.h \
    qml/tearpainter.h

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

INCLUDEPATH += $$PWD/../include

