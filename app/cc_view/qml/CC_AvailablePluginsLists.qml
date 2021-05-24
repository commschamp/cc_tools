import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import CC 1.0

import "qrc:/qml"

RowLayout {
    spacing: 6

    readonly property int forcedListHeight: 150
    readonly property int forcedListWidth: 200

    CC_PluginsListGroupBox {
        id: socketsList
        title: "Available Sockets"
        view.listView.height: forcedListHeight
        view.listView.width: forcedListWidth

        view.pluginType: CC_PluginListModel.Type_Socket
        view.pluginIid: CC_GuiState.socketPluginIid

        Connections {
            target: socketsList.view
            onPluginIidChanged: { 
                CC_GuiState.selectedSocketPluginIid = socketsList.view.pluginIid;
            }
        }
    }

    CC_PluginsListGroupBox {
        title: "Available Filters"
        view.listView.height: forcedListHeight
        view.listView.width: forcedListWidth

        view.pluginType: CC_PluginListModel.Type_Filter
    }

    CC_PluginsListGroupBox {
        id: protocolsList
        title: "Available Protocols"
        view.listView.height: forcedListHeight
        view.listView.width: forcedListWidth

        view.pluginType: CC_PluginListModel.Type_Protocol
        view.pluginIid: CC_GuiState.protocolPluginIid

        Connections {
            target: protocolsList.view
            onPluginIidChanged: { 
                CC_GuiState.selectedProtocolPluginIid = protocolsList.view.pluginIid;
            }
        }

    }
}


