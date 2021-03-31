import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import CC 1.0


ColumnLayout {
    id: root

    property string iid: "cc.TcpClientSocketPlugin"
    property var integration: CC_PluginIntegration.getIntegrationObject(iid);    

    RowLayout {
        id: hostRow
        spacing: 6
        Layout.fillWidth: true

        Label {
            text: qsTr("Host:")
        }

        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        TextField {
            id: hostText
            placeholderText: qsTr("localhost");
            text: integration.host
        }        
    }

    Connections {
        target: integration
        onSigApplyingChanged: {
            console.log("!!! Applying!!!");
            integration.host = hostText.text
        }
    }
}

