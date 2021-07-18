import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import CC 1.0

import "qrc:/qml"

ToolBar {
    id: root
    height: 40
    background: CC_ToolbarBackground {}
    // anchors.left: parent.left
    // anchors.right: parent.right

    RowLayout {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        spacing: 6

        CC_ToolButton {
            id: addButton
            image.source: "qrc:/image/add.png"
            tooltip.text: qsTr("Add Message") + " (" + addMessageShortcut.nativeText + ")";

            onClicked: {
                console.log("!!!NYI: Add new message");
            }            
        }

    }

    Shortcut {
        id: addMessageShortcut
        sequence: "Ctrl+M"
        enabled: true
        onActivated: {
            addButton.onClicked();
        }
    }
}
