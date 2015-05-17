#-------------------------------------------------
#
# Project created by QtCreator 2015-05-16T20:53:39
#
#-------------------------------------------------

QT += core gui network multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TearServer
TEMPLATE = app

SOURCES += main.cpp\
        tearserver.cpp \
    $$PWD/../include/networking/tearnetworkmanager.cpp \
    $$PWD/../include/networking/teartcpserver.cpp \
    $$PWD/../include/networking/teartcpsocket.cpp \
    handlers/tearinputhandler.cpp \
    handlers/tearclienthandler.cpp \
    capture/tearscreencapture.cpp

HEADERS  += tearserver.h \
    $$PWD/../include/networking/tearnetworkmanager.h \
    $$PWD/../include/networking/teartcpserver.h \
    common.h \
    $$PWD/../include/networking/teartcpsocket.h \
    handlers/tearinputhandler.h \
    $$PWD/../include/inputhandlerinterface.h \
    handlers/tearclienthandler.h \
    capture/tearscreencapture.h

FORMS    += tearserver.ui

#CONFIG += mobility
CONFIG += c++11

INCLUDEPATH += $$PWD/../include
