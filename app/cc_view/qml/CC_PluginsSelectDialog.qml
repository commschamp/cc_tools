import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.3 as Dialogs
import CC 1.0

import "qrc:/qml"

Dialogs.Dialog {
    id: root
    title: "Plugin Configuration"
    standardButtons: Dialogs.StandardButton.Cancel | (okEnabled ? Dialogs.StandardButton.Ok : 0)

    property bool socketValid: false
    property bool protocolValid: false
    property bool okEnabled: socketValid && protocolValid 

    ColumnLayout {
        id: mainLayout
        anchors.fill: parent

        CC_PluginsConfigToolbar {
            Layout.fillWidth: true
        }

        CC_AvailablePluginsLists {}

        ColumnLayout {
            //width: 200
            TextField {
                id: socketText
                placeholderText: qsTr("Socket") + " (" + socketShortcut.sequence + ")"
                text: CC_GuiState.socketPluginName

                Shortcut {
                    id: socketShortcut
                    sequence: "Alt+S"
                    onActivated: socketText.forceActiveFocus();
                }
            }

            CC_PluginsListView {
                Layout.fillWidth: true
                Layout.leftMargin: 20
                focus: true         

                pluginType: CC_PluginListModel.Type_Socket
                searchStr: socketText.text

                onSelectedNameChanged: {
                    CC_GuiState.socketPluginName = selectedName;
                }

                onPluginIidChanged: {
                    CC_GuiState.socketPluginIid = pluginIid;
                    root.socketValid = (pluginIid !== "");
                }
            }

            TextField {
                id: protocolText
                placeholderText: qsTr("Protocol")
                text: CC_GuiState.protocolPluginName

                Shortcut {
                    sequence: "Alt+P"
                    onActivated: protocolText.forceActiveFocus();
                }
            }                

            CC_PluginsListView {
                Layout.fillWidth: true
                Layout.leftMargin: 20
                focus: true         

                pluginType: CC_PluginListModel.Type_Protocol
                searchStr: protocolText.text

                onSelectedNameChanged: {
                    CC_GuiState.protocolPluginName = selectedName;
                }

                onPluginIidChanged: {
                    CC_GuiState.protocolPluginIid = pluginIid;
                    root.protocolValid = (pluginIid !== "");
                }
            }
        }
    }

    onAccepted: {
        if (!okEnabled) {
            onRejected();
            return;
        }
        
        console.log("accepted");
        var requiresConfirmation = 
            CC_AppMgr.requiresPluginsReloadConfirmation(
                CC_GuiState.socketPluginIid,
                CC_GuiState.filterPluginsIids,
                CC_GuiState.protocolPluginIid);

        if (requiresConfirmation) {
            CC_GuiState.activateDialog(CC_GuiState.DialogType_PluginsReloadConfirmation);
            CC_GuiState.closeCurrentDialog();
            return;
        }

        var applied = 
            CC_AppMgr.loadPlugins(
                CC_GuiState.socketPluginIid,
                CC_GuiState.filterPluginsIids,
                CC_GuiState.protocolPluginIid);

        if (!applied) {
            CC_GuiState.activateDialog(CC_GuiState.DialogType_PluginsReloadError);
        }

        CC_GuiState.closeCurrentDialog();
    }

    onRejected: {
        console.log("rejected");
        CC_GuiState.closeCurrentDialog();
    } 

    Component.onCompleted: {
        visible = true;

        // Hacky width adjustement, otherwise the dialog hides the right edge
        width = contentItem.implicitWidth + 16;
    }
}

