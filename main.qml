import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 700
    height: 480
    title: qsTr("Hello World")
    TaskForm {
        anchors.centerIn: parent
    }
}
