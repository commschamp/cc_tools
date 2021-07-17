import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import CC 1.0

import "qrc:/qml"

RowLayout {
    spacing: 6

    readonly property int forcedListHeight: 150
    readonly property int forcedConfigHeight: 200
    readonly property int forcedListWidth: 300

    CC_PluginsListWithConfig {
        id: socketsList
        groupBox.title: "Available Sockets"
        groupBox.view.listView.height: forcedListHeight
        groupBox.view.listView.width: forcedListWidth

        groupBox.view.pluginType: CC_PluginListModel.Type_Socket
        groupBox.view.pluginIid: CC_GuiState.selectedSocketPluginIid !== "" ? CC_GuiState.selectedSocketPluginIid : CC_GuiState.socketPluginIid

        configLoader.source: CC_GuiState.selectedSocketPluginConfigQml

        Connections {
            target: socketsList.groupBox.view
            onPluginIidChanged: { 
                CC_GuiState.selectedSocketPluginIid = socketsList.groupBox.view.pluginIid;
            }
        }

        Component.onCompleted: {
            if (groupBox.view.pluginIid !== "" && (CC_GuiState.selectedSocketPluginIid == "")) {
                CC_GuiState.selectedSocketPluginIid = groupBox.view.pluginIid;
            }
        }
    }

    Repeater {
        model: CC_GuiState.FilterPluginsIids > 1 ? CC_GuiState.FilterPluginsIids : 1
        CC_PluginsListWithConfig {
            groupBox.title: "Available Filters"
            groupBox.view.listView.height: forcedListHeight
            groupBox.view.listView.width: forcedListWidth

            groupBox.view.pluginType: CC_PluginListModel.Type_Filter
        }
    }

    CC_PluginsListWithConfig {
        id: protocolsList
        groupBox.title: "Available Protocols"
        groupBox.view.listView.height: forcedListHeight
        groupBox.view.listView.width: forcedListWidth

        groupBox.view.pluginType: CC_PluginListModel.Type_Protocol
        groupBox.view.pluginIid: CC_GuiState.selectedProtocolPluginIid !== "" ? CC_GuiState.selectedProtocolPluginIid : CC_GuiState.protocolPluginIid

        configLoader.source: CC_GuiState.selectedProtocolPluginConfigQml

        Connections {
            target: protocolsList.groupBox.view
            onPluginIidChanged: { 
                CC_GuiState.selectedProtocolPluginIid = protocolsList.groupBox.view.pluginIid;
            }
        }

        Component.onCompleted: {
            if (groupBox.view.pluginIid !== "" && (CC_GuiState.selectedProtocolPluginIid == "")) {
                CC_GuiState.selectedProtocolPluginIid = groupBox.view.pluginIid;
            }
        }
    }
}


