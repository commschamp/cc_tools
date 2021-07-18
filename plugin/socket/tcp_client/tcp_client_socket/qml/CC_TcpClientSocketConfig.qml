import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import CC 1.0


ColumnLayout {
    id: root

    property string iid: "cc.TcpClientSocketPlugin"
    property var integration: CC_PluginIntegration.getIntegrationObject(iid);    
    anchors.fill: parent

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
            text: integration.appliedHost

            onTextChanged: {
                integration.host = text
            }
        }        
    }

    RowLayout {
        id: portRow
        spacing: 6
        Layout.fillWidth: true

        Label {
            text: qsTr("Port:")
        }

        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        SpinBox {
            id: portValue
            from: 0
            to: 0xffff
            wheelEnabled: true
            editable: true
            value: integration.appliedPort
            Layout.minimumWidth: 80
            contentItem: TextInput {
                text: portValue.textFromValue(portValue.value, portValue.locale)
                font: portValue.font
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                readOnly: !portValue.editable
                validator: portValue.validator
                inputMethodHints: Qt.ImhFormattedNumbersOnly

                onTextChanged: {
                    portValue.value = portValue.valueFromText(text, Qt.locale());
                }

            }     

            valueFromText: function(text, locale) { 
                return Number.fromLocaleString(locale, text); 
            } 

            onValueChanged: {
                integration.port = value;
            }  
        }        
    }  

    Item {
        Layout.fillHeight: true
        Layout.fillWidth: true
    }      
}

