import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

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

    Shortcut {
        sequences: [StandardKey.Quit]
        onActivated: Qt.quit()
    }
}
