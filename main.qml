import QtQuick 2.12
import QtQuick.Window 2.12

//основано
//Using C++ Models in QML {tutorial}
//Qt Group
//https://www.youtube.com/watch?v=9BcAYDlpuT8


Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Read Sensor Arduino")

    Read_sensor {
        anchors.centerIn: parent
    }
}
