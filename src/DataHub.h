#pragma once

#include <QObject>
#include <QVariant>
#include <QMap>
#include <QMutex>

class DataHub : public QObject {
    Q_OBJECT
public:
    explicit DataHub(QObject *parent = nullptr);

    // Called by backend sources (Serial, Modbus, etc.) to update data
    void publish(const QString &key, const QVariant &value);

    // Called by QML to get the current value of a specific key
    Q_INVOKABLE QVariant getValue(const QString &key) const;

signals:
    // Emitted when any data changes. QML widgets can listen to this.
    void dataUpdated(const QString &key, const QVariant &value);

private:
    QMap<QString, QVariant> m_dataStore;
    mutable QMutex m_mutex;
};