import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "qrc:/qml"

ToolBar {
    id: root
    height: 40
    background: Rectangle {
        color: "lightgrey"
        anchors.fill: parent
    }
    anchors.left: parent.left
    anchors.right: parent.right

    RowLayout {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        spacing: 6

        CC_ToolButton {
            image.source: "qrc:/image/plugin_select.png"
            tooltip.text: qsTr("Select plugins")

            onClicked: {
                console.log("TODO: Plugin selection clicked");
            }            
        }
        
        // TODO: extra buttons from plugin
    }
}
