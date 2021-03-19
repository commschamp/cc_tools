import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import CC 1.0

import "qrc:/qml"

Dialog {
    id: root
    visible: true
    closePolicy: Dialog.NoAutoClose
    x: (parent.width - width) / 2;
    y: (parent.height - height) / 2;    
    modal: true
    title: "Plugin Configuration"
    standardButtons: Dialog.Ok | Dialog.Cancel

    property bool socketValid: false
    property bool okEnabled: socketValid // TODO: should be true when applicable

    ColumnLayout {
        width: 200
        TextField {
            id: socketText
            placeholderText: qsTr("Socket") + " (" + socketShortcut.sequence + ")";
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
            //Layout.minimumHeight: 100
            //Layout.maximumHeight: 200
            //height: 200   
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
            placeholderText: qsTr("Protocol");

            Shortcut {
                sequence: "Alt+P"
                onActivated: protocolText.forceActiveFocus();
            }
        }                
    }

    onAccepted: {
        console.log("accepted");
        var requiresConfirmation = 
            CC_AppMgr.requiresPluginsReloadConfirmation(
                CC_GuiState.socketPluginIid,
                CC_GuiState.filterPluginsIids,
                CC_GuiState.protocolPluginIid);
        if (requiresConfirmation) {
            CC_GuiState.activateDialog(CC_GuiState.DialogType_PluginsReloadConfirmation);
            return;
        }

        var applied = 
            CC_AppMgr.loadPlugins(
                CC_GuiState.socketPluginIid,
                CC_GuiState.filterPluginsIids,
                CC_GuiState.protocolPluginIid);

        if (applied) {
            CC_GuiState.activateDialog(CC_GuiState.DialogType_None);
            return;
        }

        CC_GuiState.activateDialog(CC_GuiState.DialogType_PluginsReloadError);
    }

    onRejected: {
        console.log("rejected");
        CC_GuiState.activateDialog(CC_GuiState.DialogType_None);
    } 

    Component.onCompleted: {
        var okButton = footer.standardButton(Dialog.Ok);
        okButton.enabled = Qt.binding(function() { return okEnabled; });

        // The OK button has "Alt+O" shortcut, while Cancel has "Alt+C".
        // However there is no visual indication. The code below doesn't
        // really work.

        // okButton.hoverEnabled = true;
        // okButton.ToolTip.text = dummyOk.nativeText;
        // okButton.ToolTip.visible = okEnabled && okButton.hovered;
        // okButton.ToolTip.delay = 1000;

        // cancelButton = footer.standardButton(Dialog.Cancel);
        // cancelButton.hoverEnabled = true;
        // cancelButton.ToolTip.text = dummyCancel.nativeText;
        // cancelButton.ToolTip.visible = cancelButton.hovered;
        // cancelButton.ToolTip.delay = 1000;
    }
}

