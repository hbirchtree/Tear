import QtQuick 2.4
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.2

Item {
    width: 400
    height: 400

    property alias connectBtn: button1
    property alias hostField: textField1
    property alias portField: textField2

    ColumnLayout {
        id: columnLayout1
        anchors.fill: parent

        GroupBox {
            id: groupBox1
            flat: false
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            title: qsTr("Host information")

            ColumnLayout {
                id: columnLayout2
                anchors.fill: parent

                TextField {
                    id: textField1
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    placeholderText: qsTr("IP address")
                }

                TextField {
                    id: textField2
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    placeholderText: qsTr("Port")
                }
            }
        }

        Button {
            id: button1
            text: qsTr("Connect")
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.top: groupBox1.bottom
            anchors.topMargin: 10
        }
    }
}

