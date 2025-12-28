#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "DataHub.h"
#include "SerialPortManager.h"
#include "DataSourceManager.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    DataHub dataHub;
    SerialPortManager serialManager(&dataHub);
    DataSourceManager dsManager;

    dsManager.registerSource("Serial", &serialManager);

    engine.rootContext()->setContextProperty(QStringLiteral("dataHub"), &dataHub);
    engine.rootContext()->setContextProperty(QStringLiteral("dataSourceManager"), &dsManager);

    engine.loadFromModule("LogStudio", "Main");

    return app.exec();
}