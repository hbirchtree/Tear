import QtQuick 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.0
import QtQuick.Controls 1.2

Dialog {
    signal enableKeyboard(bool state)
    signal enableMouse(bool state)
    signal enableMouseHover(bool state)
    signal enableGyro(bool state)

    property real gyroScaleX: 1.0
    property real gyroScaleY: 1.0

    width: 800
    height: 600
    visible: false
    title: qsTr("Settings")

    GroupBox {
        id: groupBox1
        anchors.fill: parent
        title: qsTr("Settings")
        Column {
            id: settingsview
            x: -8
            y: -24
            anchors.rightMargin: 10
            anchors.leftMargin: 10
            spacing: 10
            anchors.fill: parent

            CheckBox {
                id: keys
                text: qsTr("Enable keyboard input (physical)")
                checked: true
                onCheckedChanged: {
                    enableKeyboard(checked)
                }
            }
            CheckBox {
                id: mouse
                text: qsTr("Enable mouse input")
                checked: true
                onCheckedChanged: {
                    enableMouse(checked)
                }
            }
            CheckBox {
                id: mouseHover
                text: qsTr("Enable mouse hover")
                checked: false
                onCheckedChanged: {
                    enableMouseHover(checked)
                }
            }
            CheckBox {
                id: gyro
                text: qsTr("Enable gyroscopic mouse input")
                checked: false
                onCheckedChanged: {
                    enableGyro(checked)
                }
            }
            GroupBox {
                anchors.left: parent.left
                anchors.right: parent.right
                title: qsTr("Gyroscope sensitivity (X and Y)")
                Column {
                    Slider {
                        id: xscale
                        value: gyroScaleX
                        anchors.right: parent.right
                        stepSize: 0.2
                        minimumValue: -2.0
                        maximumValue: 2.0
                        onValueChanged: {
                            gyroScaleX=value
                        }
                    }
                    Slider {
                        id: yscale
                        value: gyroScaleY
                        anchors.right: parent.right
                        stepSize: 0.2
                        minimumValue: -2.0
                        maximumValue: 2.0
                        onValueChanged: {
                            gyroScaleY=value
                        }
                    }
                }

            }
        }
    }
}
