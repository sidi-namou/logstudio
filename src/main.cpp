#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "DataHub.h"
#include "SerialPortManager.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    DataHub dataHub;
    SerialPortManager serialManager(&dataHub);

    engine.rootContext()->setContextProperty(QStringLiteral("dataHub"), &dataHub);
    engine.rootContext()->setContextProperty(QStringLiteral("serialManager"), &serialManager);

    engine.loadFromModule("LogStudio", "Main");
    return app.exec();
}