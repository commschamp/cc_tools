import QtQuick 2.12
import QtQuick.Dialogs 1.3
import CC 1.0

import "qrc:/qml"

FileDialog {
    id: root
    title: qsTr("Load Plugins Configuration")
    defaultSuffix: "cfg"
    nameFilters: [ "Configuration files (*.cfg)", "All files (*)" ]
    sidebarVisible: true
    selectExisting: true

    onAccepted: {
        var loaded = 
            CC_AppMgr.loadPluginsConfig(root.fileUrl);

        CC_GuiState.closeCurrentDialog();

        if (!loaded) {
            CC_GuiState.activateDialogPrepend(CC_GuiState.DialogType_PluginsConfigLoadFailed);
        }
    }

    onRejected: {
        CC_GuiState.closeCurrentDialog();
    }

    Component.onCompleted: visible = true
}

