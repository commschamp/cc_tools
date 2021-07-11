import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import CC 1.0

RowLayout {
    id: root
    spacing: 6

    property string iid: "cc.TcpClientSocketPlugin"
    property var integration: CC_PluginIntegration.getIntegrationObject(iid);

    ToolButton {
        id: connectButton
        icon.source: connectImage.source
        Layout.alignment: Qt.AlignVCenter
        display: ToolButton.IconOnly
        visible: !integration.connected
        hoverEnabled: true

        Image {
            id: connectImage
            source: "qrc:/tcp_client_socket/image/connect.png"
            anchors.fill: parent
            anchors.margins: 2
        }

        Shortcut {
            id: connectShortcut
            sequence: "Ctrl+Alt+S"
            enabled: connectButton.visible
            onActivated: {
                connectButton.onClicked();
            }
        }          

        ToolTip.delay: 1000
        ToolTip.timeout: 5000
        ToolTip.visible: connectButton.hovered
        ToolTip.text: qsTr("Connect Socket") + " (" + connectShortcut.nativeText + ")";

        onClicked: {
            integration.connected = true;
        }
    }

    ToolButton {
        id: disconnectButton
        icon.source: disconnectImage.source
        Layout.alignment: Qt.AlignVCenter
        display: ToolButton.IconOnly
        visible: integration.connected
        hoverEnabled: true

        Image {
            id: disconnectImage
            source: "qrc:/tcp_client_socket/image/disconnect.png"
            anchors.fill: parent
            anchors.margins: 2
        }

        Shortcut {
            id: disconnectShortcut
            sequence: "Ctrl+Alt+S"
            enabled: disconnectButton.visible
            onActivated: {
                disconnectButton.onClicked();
            }
        }         

        ToolTip.delay: 1000
        ToolTip.timeout: 5000
        ToolTip.visible: disconnectButton.hovered
        ToolTip.text: qsTr("Disconnect Socket") + " (" + disconnectShortcut.nativeText + ")";        

        onClicked: {
            integration.connected = false;
        }
    }

    ToolButton {
        id: settingsButton
        icon.source: settingsImage.source
        Layout.alignment: Qt.AlignVCenter
        display: ToolButton.IconOnly
        hoverEnabled: true
        enabled: (!integration.settingsDisplayed) && (!integration.connected);
        opacity: enabled ? 1.0 : 0.4

        Image {
            id: settingsImage
            source: "qrc:/tcp_client_socket/image/cog.png"
            anchors.fill: parent
            anchors.margins: 2
        }

        Shortcut {
            id: settingsShortcut
            sequence: "Ctrl+Alt+G"
            onActivated: {
                settingsButton.onClicked();
            }
        }         

        ToolTip.delay: 1000
        ToolTip.timeout: 5000
        ToolTip.visible: disconnectButton.hovered
        ToolTip.text: qsTr("Configure Socket") + " (" + settingsShortcut.nativeText + ")";        

        onClicked: {
            integration.settingsDisplayed = true;
        }        
    }
}

