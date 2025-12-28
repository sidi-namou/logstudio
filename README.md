# logstudio
LogStudio: The Modular IoT Workbench

## Project Context
A desktop IoT application developed in C++ (Qt 6) and QML under the MIT license.
Goal: Replace PuTTY with a modular graphical dashboard (Simulink style).

## Architecture

### Backend (C++)
*   Independent of UI.
*   **DataHub**: Central Pub/Sub class.
*   Sources (Serial, SSH, Modbus) push data to DataHub.
*   Current connectivity: `QSerialPort`.

### Frontend (QML)
*   Modular interface with Drag & Drop widgets.
*   Plugin system for custom QML widgets (Gauges, Curves).
*   Data binding via keys (e.g., "temp") requested from DataHub.

## Constraints
*   **License**: MIT Strict.
*   **No GPL modules** (No Qt Charts, No QCustomPlot).
*   **Graphics**: Custom QQuickItem or MIT-compatible libraries (e.g., Qwt).
