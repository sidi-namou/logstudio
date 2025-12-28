#pragma once

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include "DataSource.h"

class SerialPortManager : public DataSource {
    Q_OBJECT
public:
    explicit SerialPortManager(DataHub* dataHub, QObject *parent = nullptr);

    Q_INVOKABLE bool connectSerial(const QString &portName, int baudRate, 
                                   const QString &dataBits = "8", const QString &parity = "None", 
                                   const QString &stopBits = "1", const QString &flowControl = "None");
    Q_INVOKABLE void disconnectSerial();

    // DataSource Interface Implementation
    bool connectSource(const QVariantMap &settings) override;
    void disconnectSource() override;
    Q_INVOKABLE void sendData(const QString &data) override;
    Q_INVOKABLE QStringList availablePorts() override;

private slots:
    void onReadyRead();

private:
    QSerialPort m_serial;
};