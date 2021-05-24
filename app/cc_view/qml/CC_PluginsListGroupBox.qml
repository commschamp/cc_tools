import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import CC 1.0

import "qrc:/qml"

GroupBox {
    id: root

    // Access params
    property alias view: view

    label: Label {
        x: root.leftPadding
        width: root.availableWidth
        text: root.title
        //color: "#21be2b"
        elide: Text.ElideRight
        horizontalAlignment: Text.AlignHCenter
        font.pointSize: 12
        font.bold: true
    }

    CC_PluginsListView {
        id: view
    }
}