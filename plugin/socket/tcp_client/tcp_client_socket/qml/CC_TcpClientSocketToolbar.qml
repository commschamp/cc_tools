import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import CC 1.0

RowLayout {
    spacing: 6

    ToolButton {
        id: connectButton
        icon.source: image.source
        Layout.alignment: Qt.AlignVCenter
        display: ToolButton.IconOnly
        //hoverEnabled: tooltip.text !== ""

        //property alias image: image
        //property alias tooltip: tooltip

        Image {
            id: image
            source: "qrc:/tcp_client_socket/image/connect.png"
            anchors.fill: parent
            anchors.margins: 2
        }

        // CC_Tooltip {
        //     id: tooltip
        //     show: root.hovered
        // }
    }


}

