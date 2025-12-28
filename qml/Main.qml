import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    width: 1024
    height: 768
    visible: true
    title: qsTr("LogStudio - IoT Workbench")

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10
        
        ConnectionPanel {
            Layout.fillWidth: true
        }

        TerminalWidget {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}