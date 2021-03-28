import QtQuick 2.12
import QtQuick.Dialogs 1.3
import CC 1.0

import "qrc:/qml"

MessageDialog {
    id: root
    title: "Plugins Reload Confirmation"
    standardButtons: StandardButton.Yes | StandardButton.No
    icon: StandardIcon.Question
    text: qsTr("Plugins need to be reloaded, all displayed messages will be lost");

    onYes: {
        var applied = 
            CC_AppMgr.loadPlugins(
                CC_GuiState.socketPluginIid,
                CC_GuiState.filterPluginsIids,
                CC_GuiState.protocolPluginIid);

        if (!applied) {
            CC_GuiState.activateDialog(CC_GuiState.DialogType_PluginsReloadError);
        }

        CC_GuiState.closeCurrentDialog();
    }

    onNo: {
        CC_GuiState.closeCurrentDialog();
    }

    Component.onCompleted: visible = true
}

