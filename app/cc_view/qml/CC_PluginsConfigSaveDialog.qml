import QtQuick 2.12
import QtQuick.Dialogs 1.3
import CC 1.0

import "qrc:/qml"

FileDialog {
    id: root
    title: qsTr("Save Plugins Configuration")
    defaultSuffix: "cfg"
    nameFilters: [ "Configuration files (*.cfg)", "All files (*)" ]
    sidebarVisible: true
    selectExisting: false

    onAccepted: {
        var saved = 
            CC_AppMgr.savePluginsConfig(
                root.fileUrl,
                CC_GuiState.selectedSocketPluginIid,
                CC_GuiState.selectedFilterPluginsIids,
                CC_GuiState.selectedProtocolPluginIid);

        CC_GuiState.closeCurrentDialog();

        if (!saved) {
            CC_GuiState.activateDialogPrepend(CC_GuiState.DialogType_PluginsConfigSaveFailed);
        }
    }

    onRejected: {
        CC_GuiState.closeCurrentDialog();
    }

    Component.onCompleted: visible = true
}

