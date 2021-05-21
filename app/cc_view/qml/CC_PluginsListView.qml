import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import CC 1.0

import "qrc:/qml"

GroupBox {
    id: root

    // Input params
    property int pluginType: CC_PluginListModel.Type_Invalid
    property string searchStr: ""
    property alias listView: listView

    // Output params
    property string selectedName: ""
    property string pluginIid: ""

    // Internal configuration
    readonly property int elemHeight: 30
    readonly property int maxElemsToShow: 6

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

    ColumnLayout {
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
                            root.selectedName = "";
                        }

                        listView.currentIndex = index;
                        root.selectedName = listView.model.getNameOf(index);
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
    }

    onSearchStrChanged: {
        listView.updateSelection();
    }
}