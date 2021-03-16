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

    property bool okEnabled: true // TODO: should be true when applicable
    property string okShortcut: "Enter"
    property string cancelShortcut: "Esc"

    ColumnLayout {
        width: 200
        TextField {
            id: socketText
            placeholderText: qsTr("Socket") + " (" + socketShortcut.sequence + ")";

            Shortcut {
                id: socketShortcut
                sequence: "Alt+S"
                onActivated: socketText.forceActiveFocus();
            }
        }

        CC_PluginListView {
            Layout.fillWidth: true
            Layout.leftMargin: 20
            height: 200   
            focus: true         

            pluginType: CC_PluginListModel.Type_Socket
            searchStr: socketText.text

            onSigPluginSelected: {
                socketText.text = name;
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

    Shortcut {
        id: dummyOk
        enabled: false
        sequence: "Alt+O"
    }

    Shortcut {
        id: dummyCancel
        enabled: false
        sequence: "Alt+C"
    }

    onAccepted: {
        console.log("accepted");
        CC_GuiState.activateDialog(CC_GuiState.DialogType_None);        
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

