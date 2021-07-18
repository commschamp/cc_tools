import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import CC 1.0

CC_BackgroundRectangle {
    radius: 5
    border.color: "black"
    border.width: 2

    Label {
        text: qsTr("Message")
        anchors.centerIn: parent
    }
}