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
        id: modeCombo
        enabled: !isConnected
        model: dataSourceManager.availableModes
        Layout.preferredWidth: 100
        onActivated: dataSourceManager.setMode(currentText)

        // Sync with backend state
        Connections {
            target: dataSourceManager
            function onCurrentModeChanged() { modeCombo.currentIndex = modeCombo.indexOfValue(dataSourceManager.currentMode) }
        }
        Component.onCompleted: currentIndex = indexOfValue(dataSourceManager.currentMode)
    }

    ComboBox {
        id: portCombo
        visible: dataSourceManager.currentMode === "Serial"
        enabled: !isConnected
        model: dataSourceManager.availablePorts()
        onPressedChanged: if(pressed) model = dataSourceManager.availablePorts()
        Layout.preferredWidth: 150
    }
    
    ComboBox {
        id: baudCombo
        visible: dataSourceManager.currentMode === "Serial"
        enabled: !isConnected
        model: [9600, 19200, 38400, 57600, 115200]
        currentIndex: 4
        Layout.preferredWidth: 100
    }

        Button {
        text: "Settings"
        visible: dataSourceManager.currentMode === "Serial"
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
                var settings = {}
                if (dataSourceManager.currentMode === "Serial") {
                    settings["port"] = portCombo.currentText
                    settings["baud"] = parseInt(baudCombo.currentText)
                    settings["dataBits"] = dataBitsCombo.currentText
                    settings["parity"] = parityCombo.currentText
                    settings["stopBits"] = stopBitsCombo.currentText
                    settings["flowControl"] = flowControlCombo.currentText
                }
                // Add other modes (SSH, Modbus) logic here in the future
                
                dataSourceManager.connectSource(settings)
            }
        }
    }
}