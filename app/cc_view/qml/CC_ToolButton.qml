import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import "qrc:/qml"

ToolButton {
    id: root
    icon.source: image.source
    Layout.alignment: Qt.AlignVCenter
    display: ToolButton.IconOnly
    hoverEnabled: tooltip.text !== ""

    property alias image: image
    property alias tooltip: tooltip

    Image {
        id: image
        anchors.fill: parent
        anchors.margins: 2
    }

    CC_Tooltip {
        id: tooltip
        show: root.hovered
    }
}

