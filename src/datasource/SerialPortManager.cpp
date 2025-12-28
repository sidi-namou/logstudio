#include "SerialPortManager.h"
#include "DataHub.h"
#include <QDateTime>
#include <QDebug>

SerialPortManager::SerialPortManager(DataHub* dataHub, QObject *parent)
    : DataSource(dataHub, parent) {
    connect(&m_serial, &QSerialPort::readyRead, this, &SerialPortManager::onReadyRead);
}

QStringList SerialPortManager::availablePorts() {
    QStringList ports;
    for (const QSerialPortInfo &info : QSerialPortInfo::availablePorts()) {
        ports << info.portName();
    }
    return ports;
}

bool SerialPortManager::connectSerial(const QString &portName, int baudRate, 
                                   const QString &dataBits, const QString &parity, 
                                   const QString &stopBits, const QString &flowControl) {
    if (m_serial.isOpen()) m_serial.close();
    
    m_serial.setPortName(portName);
    m_serial.setBaudRate(baudRate);

    // Configuration Maps
    static const QMap<QString, QSerialPort::DataBits> dataBitsMap = {
        {"5", QSerialPort::Data5}, {"6", QSerialPort::Data6},
        {"7", QSerialPort::Data7}, {"8", QSerialPort::Data8}
    };
    static const QMap<QString, QSerialPort::Parity> parityMap = {
        {"Even", QSerialPort::EvenParity}, {"Odd", QSerialPort::OddParity},
        {"Space", QSerialPort::SpaceParity}, {"Mark", QSerialPort::MarkParity},
        {"None", QSerialPort::NoParity}
    };
    static const QMap<QString, QSerialPort::StopBits> stopBitsMap = {
        {"1.5", QSerialPort::OneAndHalfStop}, {"2", QSerialPort::TwoStop},
        {"1", QSerialPort::OneStop}
    };
    static const QMap<QString, QSerialPort::FlowControl> flowControlMap = {
        {"Hardware", QSerialPort::HardwareControl}, {"Software", QSerialPort::SoftwareControl},
        {"None", QSerialPort::NoFlowControl}
    };

    m_serial.setDataBits(dataBitsMap.value(dataBits, QSerialPort::Data8));
    m_serial.setParity(parityMap.value(parity, QSerialPort::NoParity));
    m_serial.setStopBits(stopBitsMap.value(stopBits, QSerialPort::OneStop));
    m_serial.setFlowControl(flowControlMap.value(flowControl, QSerialPort::NoFlowControl));
    
    if (m_serial.open(QIODevice::ReadWrite)) {
        qDebug() << "Connected to" << portName << "Baud:" << baudRate;

        QVariantMap status;
        status["connected"] = true;
        status["port"] = portName;
        status["baud"] = baudRate;
        m_dataHub->publish("connection_status", status);

        return true;
    }

    qWarning() << "Serial Error:" << m_serial.errorString();
    QVariantMap errorStatus;
    errorStatus["connected"] = false;
    errorStatus["error"] = m_serial.errorString();
    m_dataHub->publish("connection_status", errorStatus);

    return false;
}

// Polymorphic implementation
bool SerialPortManager::connectSource(const QVariantMap &settings) {
    return connectSerial(
        settings.value("port").toString(),
        settings.value("baud").toInt(),
        settings.value("dataBits", "8").toString(),
        settings.value("parity", "None").toString(),
        settings.value("stopBits", "1").toString(),
        settings.value("flowControl", "None").toString()
    );
}

void SerialPortManager::disconnectSerial() {
    if (m_serial.isOpen()) m_serial.close();
    
    QVariantMap status;
    status["connected"] = false;
    m_dataHub->publish("connection_status", status);
}

void SerialPortManager::disconnectSource() {
    disconnectSerial();
}

void SerialPortManager::sendData(const QString &data) {
    if (m_serial.isOpen()) {
        m_serial.write(data.toUtf8());
    }
}

void SerialPortManager::onReadyRead() {
    QByteArray data = m_serial.readAll();
    // We wrap data in a map with a timestamp to ensure DataHub sees it as a "change" even if data is identical
    QVariantMap map;
    map["data"] = QString::fromUtf8(data);
    map["ts"] = QDateTime::currentMSecsSinceEpoch();
    
    m_dataHub->publish("serial_rx", map);
}