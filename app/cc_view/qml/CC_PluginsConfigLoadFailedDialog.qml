import QtQuick 2.12
import QtQuick.Dialogs 1.3
import CC 1.0

import "qrc:/qml"

MessageDialog {
    id: root
    title: qsTr("Plugins Configuration Load Failed")
    standardButtons: StandardButton.Ok
    icon: StandardIcon.Critical
    text: qsTr("Loading plugin configuration has failed.");

    onAccepted: {
        CC_GuiState.closeCurrentDialog();
    }

    onRejected: {
        CC_GuiState.closeCurrentDialog();
    }

    Component.onCompleted: visible = true
}

