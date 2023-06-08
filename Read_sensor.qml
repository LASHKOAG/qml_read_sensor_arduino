import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

import ReadSensor 1.0

Frame {
    Layout.fillWidth: true
    ListView {
        implicitWidth: 400
        implicitHeight: 400
        clip: true
        spacing: 10
        anchors.fill: parent
        model: ReadSensorModel{}
        delegate: RowLayout {
            width: parent.width
            Rectangle {
                id: r_sensor_address
                width: parent.width/4
                height: 30
                border.color: "green"
                border.width: 2
                Text {
                    id: txt_sensor_address
                    //text: qsTr("sensor_address")
                    text: model.sensor_address
                }
            }
            Rectangle {
                id: r_sensor_name
                width: parent.width/4
                height: 30
                border.color: "green"
                border.width: 2
                Text {
                    id: txt_sensor_name
                    //text: qsTr("sensor_name")
                    text: model.sensor_name
                }
            }
            Rectangle {
                id: r_sensor_data
                width: parent.width/5
                height: 30
                border.color: "green"
                border.width: 2
                Text {
                    id: txt_sensor_data
                    //text: qsTr("sensor_data")
                    text: model.sensor_data
                }
            }
        }

    }
}
