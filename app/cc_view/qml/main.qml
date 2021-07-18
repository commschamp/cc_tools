import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import CC 1.0

import "qrc:/qml"

ApplicationWindow {
    id: root
    visible: true
    visibility: "Maximized"
    title: qsTr("CommsChampion View")

    header: CC_Toolbar {}

    RowLayout {
        anchors.margins: 5
        anchors.fill: parent
        spacing: 5
        ColumnLayout {
            Layout.fillHeight: true
            spacing: 5
            CC_ExchangedMessages {
                Layout.fillHeight: true
                Layout.fillWidth: true
            }

            CC_MessagesToSend {
                Layout.fillHeight: true
                Layout.fillWidth: true
            }
        }

        CC_MessageInfo {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
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
