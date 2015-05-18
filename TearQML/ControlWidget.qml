import QtQuick 2.4

ControlWidgetForm {
    gyroLock.onCheckedChanged: {
        if(gyroLock.checked){
            gyroY.value = Qt.binding(function() {return gyroX.value})
            gyroY.enabled=false
        }else{
            gyroY.value = 1.0
            gyroY.enabled=true
        }
    }
}

