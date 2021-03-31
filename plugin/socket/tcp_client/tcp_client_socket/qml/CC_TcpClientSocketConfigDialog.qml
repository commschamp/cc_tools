import QtQuick 2.12
import QtQuick.Dialogs 1.3 as Dialogs
import CC 1.0

import "qrc:/tcp_client_socket/qml"

Dialogs.Dialog {
    id: root
    title: "Socket Configuration"
    standardButtons: Dialogs.StandardButton.Cancel | Dialogs.StandardButton.Ok

    property alias integration: config.integration

    CC_TcpClientSocketConfig {
        id: config
    }

    onAccepted: {
        console.log("Accepted");
        integration.applying = true;
        integration.settingsDisplayed = false;
    }

    onRejected: {
        console.log("Rejected");
        integration.settingsDisplayed = false;
    }

    Component.onCompleted: visible=true
}

