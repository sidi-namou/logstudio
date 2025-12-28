cmake_minimum_required(VERSION 3.16)

project(LogStudio VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 REQUIRED COMPONENTS Quick SerialPort)

qt_standard_project_setup()

qt_add_executable(appLogStudio
    src/main.cpp
)

# Enable testing for future Unity tests
enable_testing()

# Include directories
target_include_directories(appLogStudio PRIVATE src src/datasource)

qt_add_qml_module(appLogStudio
    URI LogStudio
    VERSION 1.0
    SOURCES
            src/DataHub.cpp
            src/DataHub.h
            src/datasource/SerialPortManager.cpp
            src/datasource/SerialPortManager.h
            src/datasource/DataSource.cpp
            src/datasource/DataSource.h
            src/datasource/DataSourceManager.cpp
            src/datasource/DataSourceManager.h
            # src/plot/ (Future Plotting Widgets)
    QML_FILES qml/Main.qml
              qml/TerminalWidget.qml
              qml/ConnectionPanel.qml
)

target_link_libraries(appLogStudio
    PRIVATE Qt6::Quick Qt6::SerialPort
)

install(TARGETS appLogStudio
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
