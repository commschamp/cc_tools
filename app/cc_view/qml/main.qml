import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import CC 1.0

import "qrc:/qml"

ApplicationWindow {
    visible: true
    visibility: "Maximized"
    title: qsTr("CommsChampion View")

    header: CC_Toolbar {}

    Label {
        text: qsTr("NYI")
        anchors.centerIn: parent
    }

    Loader {
        source: CC_GuiState.dialogQml
        active: source !== ""
        anchors.fill: parent
    }        

    Shortcut {
        sequence: "Ctrl+Q"
        context: Qt.ApplicationShortcut
        onActivated: Qt.quit()
    }
}
