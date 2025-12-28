import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

RowLayout {
    spacing: 10
    
    property bool isConnected: false

    // Listen to DataHub for connection status changes
    Connections {
        target: dataHub
        function onDataUpdated(key, value) {
            if (key === "connection_status") {
                isConnected = value.connected
            }
        }
    }

    ComboBox {
        id: portCombo
        enabled: !isConnected
        model: dataSourceManager.availablePorts()
        onPressedChanged: if(pressed) model = dataSourceManager.availablePorts()
        Layout.preferredWidth: 150
    }
    
    ComboBox {
        id: baudCombo
        enabled: !isConnected
        model: [9600, 19200, 38400, 57600, 115200]
        currentIndex: 4
        Layout.preferredWidth: 100
    }

        Button {
        text: "Settings"
        enabled: !isConnected
        onClicked: settingsDialog.open()
    }

    Dialog {
        id: settingsDialog
        title: "Serial Settings"
        anchors.centerIn: Overlay.overlay
        modal: true
        standardButtons: Dialog.Ok

        GridLayout {
            columns: 2
            rowSpacing: 10
            columnSpacing: 10

            Label { text: "Data Bits:" }
            ComboBox {
                id: dataBitsCombo
                model: ["5", "6", "7", "8"]
                currentIndex: 3 // Default 8
            }

            Label { text: "Parity:" }
            ComboBox {
                id: parityCombo
                model: ["None", "Even", "Odd", "Space", "Mark"]
                currentIndex: 0
            }

            Label { text: "Stop Bits:" }
            ComboBox {
                id: stopBitsCombo
                model: ["1", "1.5", "2"]
                currentIndex: 0
            }

            Label { text: "Flow Control:" }
            ComboBox {
                id: flowControlCombo
                model: ["None", "Hardware", "Software"]
                currentIndex: 0
            }
        }
    }

    Button {
        text: isConnected ? "Disconnect" : "Connect"
        highlighted: isConnected
        onClicked: {
            if (isConnected) {
                dataSourceManager.disconnectSource()
            } else {
                dataSourceManager.connectSource({
                    "port": portCombo.currentText,
                    "baud": parseInt(baudCombo.currentText),
                    "dataBits": dataBitsCombo.currentText,
                    "parity": parityCombo.currentText,
                    "stopBits": stopBitsCombo.currentText,
                    "flowControl": flowControlCombo.currentText
                })
            }
        }
    }
}