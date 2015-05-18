import QtQuick 2.4
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.0

Item {
    width: 600
    height: 400

    property alias gyroX: gyroXScale
    property alias gyroY: gyroYScale
    property alias gyroLock: gyroLockRatio
    property alias gyroEnable: gyroGroup

    property alias mouseClick: mouseClick
    property alias mouseEnable: mouseGroup

    property alias keyboardEnable: keyboard

    property alias close: closeBtn

    ColumnLayout {
        id: select
        spacing: 2
        anchors.fill: parent
        GroupBox {
            id: mouse
            height: 300
            checkable: true
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            title: qsTr("Enable mouse")

            ColumnLayout {
                id: mouseGroup
                anchors.fill: parent

                CheckBox {
                    id: mouseClick
                    text: qsTr("Tap to click")
                    checked: true
                }
            }
        }
        CheckBox {
            id: keyboard
            text: qsTr("Enable keyboard")
            checked: true
            anchors.top: mouse.bottom
            anchors.topMargin: 10
        }
        GroupBox {
            id: gyroGroup
            height: 300
            checked: false
            anchors.topMargin: 10
            anchors.top: keyboard.bottom
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.leftMargin: 0
            checkable: true
            title: qsTr("Enable gyroscope")
            ColumnLayout {
                id: columnLayout1
                anchors.fill: parent
                CheckBox {
                    id: gyroLockRatio
                    text: qsTr("Lock ratio")
                }
                RowLayout {
                    id: rowLayout1
                    height: 100
                    anchors.top: gyroLockRatio.bottom
                    anchors.topMargin: 5
                    anchors.right: parent.right
                    anchors.left: parent.left
                    anchors.leftMargin: 0

                    Label {
                        id: label1
                        text: qsTr("X")
                    }

                    Slider {
                        id: gyroXScale
                        minimumValue: -2
                        value: 1
                        maximumValue: 2
                        anchors.left: label1.right
                        anchors.leftMargin: 5
                        anchors.right: parent.right
                        anchors.rightMargin: 0
                    }
                }
                RowLayout {
                    id: rowLayout2
                    height: 100
                    anchors.top: rowLayout1.bottom
                    anchors.topMargin: 5
                    anchors.right: parent.right
                    anchors.left: parent.left
                    anchors.leftMargin: 0

                    Label {
                        id: label2
                        text: qsTr("Y")
                    }

                    Slider {
                        id: gyroYScale
                        value: 1
                        minimumValue: -2
                        maximumValue: 2
                        anchors.right: parent.right
                        anchors.rightMargin: 0
                        anchors.left: label2.right
                        anchors.leftMargin: 5
                    }
                }
            }
        }

        Button {
            id: closeBtn
            text: qsTr("Close")
            anchors.topMargin: 10
            anchors.top: gyroGroup.bottom
        }
    }
}

