import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import CC 1.0

import "qrc:/qml"

ListView {
    id: root
    currentIndex: -1
    height: model.count > maxElemsToShow ? (maxElemsToShow * elemHeight) : contentHeight
    ScrollBar.vertical: ScrollBar {}

    // Input params
    property int pluginType: CC_PluginListModel.Type_Invalid
    property string searchStr: ""

    // Output params
    property string selectedName: ""
    property string pluginIid: ""

    // Internal configuration
    readonly property int elemHeight: 30
    readonly property int maxElemsToShow: 6

    model: CC_PluginListModel {
        pluginType: root.pluginType
    }

    delegate: Rectangle {
        id: elem
        color: selected ? "lightsteelblue" : "gainsboro"
        height: root.elemHeight
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
                var indexChanged = root.currentIndex != index;
                if (!indexChanged) {
                    root.currentIndex = -1;    
                    root.selectedName = "";
                }

                root.currentIndex = index;
                root.selectedName = root.model.getNameOf(index);
            }
        }

        ToolTip.visible: mouseArea.containsMouse && (ToolTip.text !== "")
        ToolTip.text: root.model.getDescriptionOf(index);
        ToolTip.delay: 1000
    }

    onSearchStrChanged: {
        updateSelection();
    }

    Component.onCompleted: {
        updateSelection();
    }

    function updateSelection() {
        if (searchStr === "") {
            currentIndex = -1;
            updateIid();
            return;
        }

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
            updateIid();
            return;    
        }

        currentIndex = substrIdx;
        updateIid();
    }

    function updateIid() {
        var iidStr = "";
        do {
            if (currentIndex < 0) {
                break;
            }

            var searchStrTmp = searchStr.toLowerCase();
            if (model.getNameOf(currentIndex).toLowerCase() != searchStrTmp) {
                break;
            }

            iidStr = model.getIidOf(currentIndex);
        } while (false);

        pluginIid = iidStr;
    }
}















