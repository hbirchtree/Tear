import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import TearProvider 1.0

ApplicationWindow {
    title: qsTr("Hello World")
    width: 640
    height: 480
    visible: true
    color: "black"

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: {
//                    test.socketConnect("127.0.0.1",46601)
                    inputSocket.socketConnect("192.168.10.108",46600)
                }
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
    }
    TearInputSocket {
        id: inputSocket
        onAnnounceAVSource: {
            displayPainter.socketConnect(host,port)
        }
    }

    MouseArea {
        anchors.fill:parent
        onClicked: {
            inputSocket.sendInput(5,100,100)
        }
    }

    MessageDialog {
        id: messageDialog
        title: qsTr("May I have your attention, please?")

        function show(caption) {
            messageDialog.text = caption;
            messageDialog.open();
        }
    }
}
