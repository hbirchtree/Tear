import QtQuick 2.4

ConnectDialogForm {
    signal requestConnect(string host,int port)

    hostField.onTextChanged: {
        hostField.textColor = "#000000"
    }
    portField.onTextChanged: {
        portField.textColor = "#000000"
    }

    connectBtn.onClicked: {
        var pattIPV4 = /\d+.\d+.\d+.\d+/;
        var pattHostName = /\w+\.[A-Za-z]+/;
        if(hostField.text.match(pattIPV4)/*||hostField.text.match(pattHostName)*/)
            if(portField.text.match(/\d+/)){
                requestConnect(hostField.text,portField.text)
            }else
                portField.textColor = "#FF0000"
        else
            hostField.textColor = "#FF0000"
    }
}
