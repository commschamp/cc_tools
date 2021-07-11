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
                    CC_GuiState.activateDialogPrepend(CC_GuiState.DialogType_PluginsConfigLoad);
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

            CC_ToolButton {
                id: saveToolbutton
                image.source: "qrc:/image/save_as.png"
                tooltip.text: qsTr("Save") +  " (" + openShortcut.nativeText + ")";

                onClicked: {
                    CC_GuiState.activateDialogPrepend(CC_GuiState.DialogType_PluginsConfigSave);
                }            

                Shortcut {
                    id: saveShortcut
                    sequence: "Ctrl+S"
                    enabled: true
                    onActivated: {
                        saveToolbutton.onClicked();
                    }
                }
            }
        }
    }
