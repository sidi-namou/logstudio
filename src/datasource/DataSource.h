#pragma once

#include <QObject>
#include <QVariantMap>

class DataHub;

class DataSource : public QObject {
    Q_OBJECT
public:
    explicit DataSource(DataHub* dataHub, QObject *parent = nullptr);
    virtual ~DataSource() = default;

    // Polymorphic Interface
    Q_INVOKABLE virtual bool connectSource(const QVariantMap &settings) = 0;
    Q_INVOKABLE virtual void disconnectSource() = 0;
    Q_INVOKABLE virtual void sendData(const QString &data) = 0;
    Q_INVOKABLE virtual QStringList availablePorts() = 0;

protected:
    DataHub* m_dataHub;
};