import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import CC 1.0

import "qrc:/qml"

    ToolBar {
        id: toolbar
        height: 40
        background: CC_ToolbarBackground {}

        RowLayout {
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            spacing: 6

            CC_ToolButton {
                id: openToolbutton
                image.source: "qrc:/image/folder.png"
                tooltip.text: qsTr("Open") +  " (" + openShortcut.nativeText + ")";

                onClicked: {
                    console.log("TODO: plugin configuration open");
                }            

                Shortcut {
                    id: openShortcut
                    sequence: "Ctrl+O"
                    enabled: true
                    onActivated: {
                        openToolbutton.onClicked();
                    }
                }

            }
        }
    }
