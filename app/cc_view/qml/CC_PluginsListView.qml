import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import CC 1.0

import "qrc:/qml"

ColumnLayout {
    id: root
    // Input params
    property int pluginType: CC_PluginListModel.Type_Invalid
    property string searchStr: ""
    property alias listView: listView

    // Output params
    // property string selectedName: ""
    property string pluginIid: ""

    // Internal configuration
    readonly property int elemHeight: 30
    readonly property int maxElemsToShow: 6

    anchors.fill: parent
    ListView {
        id: listView
        currentIndex: -1
        height: listView.model.count > maxElemsToShow ? (maxElemsToShow * elemHeight) : contentHeight
        
        ScrollBar.vertical: ScrollBar {}

        model: CC_PluginListModel {
            pluginType: root.pluginType
        }

        delegate: Rectangle {
            id: elem
            border.color: ListView.isCurrentItem ? "blue" : color
            height: root.elemHeight
            radius: 5
            anchors.left: parent.left
            anchors.right: parent.right

            Text {
                text: name
                anchors.left: parent.left
                anchors.leftMargin: 5
                anchors.rightMargin: 5
                anchors.verticalCenter: parent.verticalCenter
            }

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                hoverEnabled: true

                onClicked: {
                    var indexChanged = listView.currentIndex != index;
                    if (!indexChanged) {
                        listView.currentIndex = -1;    
                        return;
                    }

                    listView.currentIndex = index;
                    root.pluginIid = listView.model.getIidOf(index);
                }
            }

            ToolTip.visible: mouseArea.containsMouse && (ToolTip.text !== "")
            ToolTip.text: listView.model.getDescriptionOf(index);
            ToolTip.delay: 1000
        }

        Component.onCompleted: {
            updateSelection();
        }

        function updateSelection() {
            if (pluginIid === "") {
                return;
            }

            for (var idx = 0; idx < model.rowCount(); ++idx) {
                var pluginIidTmp = model.getIidOf(idx);
                if (pluginIid === pluginIidTmp) {
                    currentIndex = idx;
                    break;
                }
            }
        }
    }
}
