import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import CC 1.0

CC_BackgroundRectangle {
    radius: 5
    border.color: "black"
    border.width: 2

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 5

        CC_ExchangedMessagesToolbar {
            Layout.fillWidth: true
            Layout.minimumHeight: 40
        }

        Label {
            text: qsTr("Send")
            Layout.fillWidth: true
        }        

        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }

}