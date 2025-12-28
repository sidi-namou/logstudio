# logstudio
LogStudio: The Modular IoT Workbench

## Project Context
A desktop IoT application developed in C++ (Qt 6) and QML under the MIT license.
Goal: Replace PuTTY with a modular graphical dashboard (Simulink style).

## Architecture

### Backend (C++)
*   Independent of UI.
*   **DataHub**: Central Pub/Sub class.
*   **DataSource**: Abstract base class for data providers (Polymorphism).
*   Sources (Serial, SSH, Modbus) push data to DataHub.
*   Current connectivity: `QSerialPort` via `SerialPortManager`.

### Frontend (QML)
*   Modular interface with Drag & Drop widgets.
*   **TerminalWidget**: Serial terminal with input/output and clear screen.
*   **ConnectionPanel**: Hardware connection settings (Port, Baud, Parity, etc.).
*   Plugin system for custom QML widgets (Gauges, Curves).
*   Data binding via keys (e.g., "temp") requested from DataHub.

## Project Structure
*   `src/`: C++ Backend source code.
    *   `datasource/`: Data providers (Serial, Modbus, etc.).
    *   `plot/`: Plotting logic (Future).
*   `qml/`: QML Frontend resources.
*   `tests/`: Unit tests.

## Constraints
*   **License**: MIT Strict.
*   **No GPL modules** (No Qt Charts, No QCustomPlot).
*   **Graphics**: Custom QQuickItem or MIT-compatible libraries (e.g., Qwt).
