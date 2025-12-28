import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10

        // Terminal Output
        ScrollView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            
            TextArea {
                id: terminalOutput
                readOnly: true
                font.family: "Courier New"
                background: Rectangle { color: "#1e1e1e" }
                color: "#00ff00"
                
                Connections {
                    target: dataHub
                    function onDataUpdated(key, value) {
                        if (key === "serial_rx") {
                            terminalOutput.append(value.data)
                        }
                    }
                }
            }
        }

        // Input Area
        RowLayout {
            Layout.fillWidth: true
            
            ComboBox {
                id: modeSelector
                model: dataSourceManager.availableModes
                onActivated: dataSourceManager.setMode(currentText)
                Layout.preferredWidth: 100
            }

            TextField {
                id: inputField
                Layout.fillWidth: true
                placeholderText: "Send command..."
                onAccepted: sendBtn.clicked()
            }
            
            Button {
                id: sendBtn
                text: "Send"
                onClicked: {
                    dataSourceManager.sendData(inputField.text)
                    inputField.text = ""
                }
            }
            
            Button {
                text: "Clear"
                onClicked: terminalOutput.clear()
            }
        }
    }
}