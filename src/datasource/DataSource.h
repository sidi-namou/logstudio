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
    virtual bool connectSource(const QVariantMap &settings) = 0;
    virtual void disconnectSource() = 0;
    virtual void sendData(const QString &data) = 0;

protected:
    DataHub* m_dataHub;
};