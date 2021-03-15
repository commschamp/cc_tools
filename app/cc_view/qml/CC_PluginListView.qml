import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import CC 1.0

import "qrc:/qml"

ListView {
    id: root

    // Input params
    property int pluginType: CC_PluginListModel.Type_Invalid
    property string searchStr: ""

    signal sigPluginSelected(string name)

    model: CC_PluginListModel {
        pluginType: root.pluginType
    }

    delegate: Rectangle {
        id: elem
        color: selected ? "lightsteelblue" : "gainsboro"
        height: 30
        radius: 5
        anchors.left: parent.left
        anchors.right: parent.right

        property bool selected: index == root.currentIndex
        focus: selected

        Text {
            anchors.centerIn: parent
            text: name
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            hoverEnabled: true

            onClicked: {
                console.log("Clicked: " + index);
                root.currentIndex = index;
                root.sigPluginSelected(root.model.getNameOf(index));
            }
        }

        ToolTip.visible: mouseArea.containsMouse
        ToolTip.text: (0 <= root.currentIndex) ? root.model.getDescriptionOf(root.currentIndex) : "";
        ToolTip.delay: 1000
    }

    onSearchStrChanged: {
        var searchStrTmp = searchStr.toLowerCase();
        var startsIdx = -1;
        var substrIdx = -1;
        for (var idx = 0; idx < model.rowCount(); ++idx) {
            var pluginNameTmp = model.getNameOf(idx).toLowerCase();
            if ((startsIdx < 0) && pluginNameTmp.startsWith(searchStrTmp)) {
                startsIdx = idx;
                break;
            }

            if ((substrIdx < 0) && (pluginNameTmp.includes(searchStrTmp))) {
                substrIdx = idx;
                continue;
            }
        }

        if (0 <= startsIdx) {
            currentIndex = startsIdx;
            return;    
        }

        currentIndex = substrIdx;
    }
}















