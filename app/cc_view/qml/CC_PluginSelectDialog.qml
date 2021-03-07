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
        CC_GuiState.activateDialog(CC_GuiState.DialogType_None);        
    }

    onRejected: {
        console.log("rejected");
        CC_GuiState.activateDialog(CC_GuiState.DialogType_None);
    } 
}

