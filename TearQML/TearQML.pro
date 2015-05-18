TEMPLATE = app

QT += qml quick widgets multimedia sensors

CONFIG += c++11

SOURCES += main.cpp \
    ../include/networking/teartcpsocket.cpp
HEADERS += \
    ../include/networking/teartcpsocket.h \
    qml/tearpainter.h \
    qml/tearinput.h \
    qml/eventcapture.h

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

INCLUDEPATH += $$PWD/../include

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

