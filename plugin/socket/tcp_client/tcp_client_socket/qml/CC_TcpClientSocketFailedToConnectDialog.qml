import QtQuick 2.12
import QtQuick.Dialogs 1.3 as Dialogs
import CC 1.0

import "qrc:/tcp_client_socket/qml"

Dialogs.MessageDialog {
    id: root
    title: "Failed to Connect"
    standardButtons: Dialogs.StandardButton.Ok

    property string iid: "cc.TcpClientSocketPlugin"
    property var integration: CC_PluginIntegration.getIntegrationObject(iid);  
    modality: Qt.WindowModal
    icon : Dialogs.StandardIcon.Warning

    text: qsTr("Failed to connect to \'") + hostStr + ":" + integration.port + "\'."

    property string hostStr: integration.host === "" ? "localhost" : integration.host

    onAccepted: {
        CC_PluginIntegration.closeCurrentDialog();
    }

    onRejected: {
        CC_PluginIntegration.closeCurrentDialog();
    }

    Component.onCompleted: visible=true
}

