import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import CC 1.0

import "qrc:/qml"

ColumnLayout {
    id: root
    spacing: 6

    property alias groupBox: groupBox
    property alias configGroupBox: configGroupBox
    property alias configLoader: configLoader

    CC_PluginsListGroupBox {
        id: groupBox
        Layout.fillWidth: true
    }

    GroupBox {
        id: configGroupBox
        title: qsTr("Configuration")
        //Layout.minimumWidth: groupBox.width
        Layout.fillWidth: true

        label: Label {
            x: configGroupBox.leftPadding
            width: configGroupBox.availableWidth
            text: configGroupBox.title
            //color: "#21be2b"
            elide: Text.ElideRight
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 12
            font.bold: true
        }

        ColumnLayout {
            anchors.fill: parent
            ScrollView {
                Layout.fillWidth: true
                Layout.minimumHeight: 200
                Loader {
                    id: configLoader
                    anchors.fill:parent
                }
            }

            Item {
                Layout.fillWidth: true
                Layout.fillHeight: true
            }              
        }  
    }

    Item {
        Layout.fillHeight: true
        Layout.fillWidth: true
    } 
}