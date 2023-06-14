import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

import ReadSensor 1.0

ColumnLayout {
    Frame {
        Layout.fillWidth: true

        ListView {
            id: lv_read_sensor
            implicitWidth: 400
            implicitHeight: 300
            clip: true
            spacing: 10
            anchors.fill: parent
            model: ReadSensorModel{
                id: rs_model
                sensorList: readSensor
            }
            delegate: Component {
                Item {
                    id: line_data
                    width: parent.width
                    height: 30
                    //color: lv_read_sensor.currentIndex === index ? "lightgrey" : "#00000000"
                    MouseArea {
                        anchors.fill: parent
                        onClicked:{
                            lv_read_sensor.currentIndex = index
                            //console.log("lv_read_sensor.currentIndex: " + lv_read_sensor.currentIndex)
                        }
                    }

                    TextField {
                        id: txt_sensor_address
                        implicitWidth: parent.width/6
                        height: 30
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter

                        onPressed: {
                            //console.log("onPressed: + " + index)
                            lv_read_sensor.currentIndex = index
                            //console.log("lv_read_sensor.currentIndex: " + lv_read_sensor.currentIndex)
                        }

                        placeholderText: "0x...."
                        font.pixelSize: 15
                        background: Rectangle {
                            border.color: "green"
                            border.width: txt_sensor_address.activeFocus ? 3 : 2
                            //                    border.color: txt_sensor_address.enabled ? "green" : "transparent"

                            //                        //                                Image {
                            //                        //                                    width: 10
                            //                        //                                    height: 10
                            //                        //                                    source: "qrc:///inner.png"
                            //                        //                                    anchors.verticalCenter: parent.verticalCenter
                            //                        //                                    anchors.left: parent.left
                            //                        //                                    anchors.leftMargin: 10
                            //                        //                                }
                        }

                        text: "0x" + model.sensor_address.toString(16)
                    }

                    TextField {
                        id: txt_sensor_name
                        implicitWidth: parent.width/3
                        height: 30
                        anchors.centerIn: parent
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter

                        onPressed: {
                            //console.log("onPressed: + " + index)
                            lv_read_sensor.currentIndex = index
                            //console.log("lv_read_sensor.currentIndex: " + lv_read_sensor.currentIndex)
                        }

                        placeholderText: "0x...."
                        font.pixelSize: 15
                        background: Rectangle {
                            border.color: "green"
                            border.width: txt_sensor_name.activeFocus ? 3 : 2
                            //                    border.color: txt_sensor_address.enabled ? "green" : "transparent"

                            //                        //                                Image {
                            //                        //                                    width: 10
                            //                        //                                    height: 10
                            //                        //                                    source: "qrc:///inner.png"
                            //                        //                                    anchors.verticalCenter: parent.verticalCenter
                            //                        //                                    anchors.left: parent.left
                            //                        //                                    anchors.leftMargin: 10
                            //                        //                                }
                        }

                        text: model.sensor_name
                    }
                    Rectangle {
                        id: r_sensor_data
                        implicitWidth: parent.width/6
                        height: 30
                        border.color: "green"
                        border.width: 2
                        anchors.right: parent.right
                        anchors.rightMargin: 10
                        Text {
                            id: txt_sensor_data
                            anchors.centerIn: parent
                            //                            horizontalAlignment: Text.AlignHCenter
                            //                            verticalAlignment: Text.AlignVCenter
                            //text: qsTr("sensor_data")
                            text: model.sensor_data
                        }
                    }

                }

            }
            highlight: Rectangle {
                color: "lightgray"
            }
            focus: true
            onCurrentItemChanged:{
                //console.log(rs_model.get(lv_read_sensor.currentIndex).name + ' selected')
                //console.log("onCurrentItemChanged:")
            }
        }
    }
    RowLayout {
        Button {
            id: btn_add
            text: qsTr("Add new item")
            Layout.fillWidth: true
            onClicked: {
                readSensor.appendItem()
//                lv_read_sensor.focus = true
                lv_read_sensor.currentIndex = rs_model.get_size() - 1
            }
        }
        Button {
            id: btn_remove
            text: qsTr("Remove sensor")
            Layout.fillWidth: true
            onClicked: readSensor.removeCompletedItems(lv_read_sensor.currentIndex)
        }
    }

    RowLayout {
        Button {
            id: btn_on
            text: qsTr("On")
            Layout.fillWidth: true
            onClicked: {
                readSensor.turn_on_led()
            }
        }
        Button {
            id: btn_off
            text: qsTr("Off")
            Layout.fillWidth: true
            onClicked: readSensor.turn_off_led()
        }
    }
}
