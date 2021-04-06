import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import CC 1.0

import "qrc:/qml"

RowLayout {
    spacing: 6

    readonly property int forcedListHeight: 150
    readonly property int forcedListWidth: 200

    CC_PluginsListView {
        focus: true         
        height: forcedListHeight
        width: forcedListWidth

        pluginType: CC_PluginListModel.Type_Socket
    }

    CC_PluginsListView {
        focus: true         
        height: forcedListHeight
        width: forcedListWidth

        pluginType: CC_PluginListModel.Type_Filter
    }

    CC_PluginsListView {
        focus: true         
        height: forcedListHeight
        width: forcedListWidth

        pluginType: CC_PluginListModel.Type_Protocol
    }
}


