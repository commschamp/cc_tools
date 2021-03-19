import QtQuick 2.12
import QtQuick.Dialogs 1.3
import CC 1.0

import "qrc:/qml"

MessageDialog {
    id: root
    title: "Plugins Reload Error"
    standardButtons: StandardButton.Ok
    icon: StandardIcon.Critical
    text: qsTr("Plugins reload failed");

    onAccepted: {
        CC_GuiState.activateDialog(CC_GuiState.DialogType_None);
    }

    Component.onCompleted: visible = true
}

