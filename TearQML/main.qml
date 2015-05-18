import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtSensors 5.0
import TearProvider 1.0

ApplicationWindow {
    title: qsTr("Tear Client")
    width: 640
    height: 480
    visible: true
//    visibility: "FullScreen"

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            MenuItem {
                text: qsTr("C&onnect")
                onTriggered: inputSocket.socketConnect("192.168.10.108",46600)
            }
            MenuItem {
                text: qsTr("&Disconnect")
                onTriggered: inputSocket.socketDisconnect()
            }
            MenuItem {
                text: qsTr("&Settings")
                onTriggered: settings.visible=true
            }
            MenuItem {
                text: qsTr("E&xit")
                onTriggered: Qt.quit();
            }
        }
    }

    TearPainter {
        id: displayPainter
        anchors.fill:parent
        antialiasing: true
        onTargetAreaChanged: {
            inputArea.screenArea = targetArea
        }
    }
    TearInputSocket {
        id: inputSocket
        onAnnounceAVSource: {
//            displayPainter.socketConnect(host,port)
        }
        onAnnounceScreenDimensions: {
            inputArea.mouseArea = Qt.rect(x,y,w,h)
        }
    }

    TearInputArea {
        id: inputArea
        anchors.fill:parent
        onNewEvent: {
            inputSocket.sendInput(type,v1,v2)
        }
        focus: true
    }

    Gyroscope {
        id: gyroscope
        dataRate: 50
        active:false
        onReadingChanged: {
            inputSocket.sendInput(87,-reading.x*settings.gyroX.value,reading.y*settings.gyroY.value)
        }
    }

//    ControlPanel {
//        id: settings
//        onEnableGyro: {
//            gyroscope.active = state
//            console.log("Gyro:"+state)
//        }
//        onEnableKeyboard: {
//            inputArea.captureKeys = state
//            console.log("Keyboard:"+state)
//        }
//        onEnableMouse: {
//            inputArea.captureMouse = state
//            console.log("Mouse:"+state)
//        }
//        onEnableMouseHover: {
//            inputArea.tapClick = !state
//            console.log("Hover:"+state)
//        }
//    }
    ControlWidget{
        id: settings
        anchors.fill:parent
        visible: false
        gyroEnable.onCheckedChanged:{
            console.log(gyroEnable.checked)
            gyroscope.active = gyroEnable.checked
        }
        close.onClicked: {
            settings.visible=false
        }
    }
}
