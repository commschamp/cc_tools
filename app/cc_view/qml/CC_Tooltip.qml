import QtQuick 2.12
import QtQuick.Controls 2.12

Item {
    id: root

    anchors.fill: parent

    property string text: ""
    property bool show: true    

    ToolTip.delay: 1000
    ToolTip.timeout: 5000
    ToolTip.visible: show && text !== ""
    ToolTip.text: text
}