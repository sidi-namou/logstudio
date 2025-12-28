#include "DataHub.h"
#include <QDebug>

DataHub::DataHub(QObject *parent) : QObject(parent) {}

void DataHub::publish(const QString &key, const QVariant &value) {
    QMutexLocker locker(&m_mutex);
    
    // Only emit if value actually changed or if we want continuous streams
    if (m_dataStore[key] != value) {
        m_dataStore[key] = value;
        locker.unlock(); // Unlock before emitting to prevent deadlocks
        
        emit dataUpdated(key, value);
    }
}

QVariant DataHub::getValue(const QString &key) const {
    QMutexLocker locker(&m_mutex);
    return m_dataStore.value(key, QVariant());
}