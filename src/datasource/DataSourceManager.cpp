#include "DataSourceManager.h"

DataSourceManager::DataSourceManager(QObject *parent) : QObject(parent) {}

void DataSourceManager::registerSource(const QString &name, DataSource* source) {
    m_sources[name] = source;
    emit modesChanged();
    
    // Auto-select first source if none selected
    if (!m_currentSource) {
        setMode(name);
    }
}

void DataSourceManager::setMode(const QString &mode) {
    if (m_sources.contains(mode)) {
        if (m_currentSource != m_sources[mode]) {
            m_currentSource = m_sources[mode];
            m_currentMode = mode;
            emit currentSourceChanged();
            emit currentModeChanged();
        }
    }
}

bool DataSourceManager::connectSource(const QVariantMap &settings) {
    if (m_currentSource) {
        return m_currentSource->connectSource(settings);
    }
    return false;
}

void DataSourceManager::disconnectSource() {
    if (m_currentSource) {
        m_currentSource->disconnectSource();
    }
}

void DataSourceManager::sendData(const QString &data) {
    if (m_currentSource) {
        m_currentSource->sendData(data);
    }
}

QStringList DataSourceManager::availablePorts() {
    if (m_currentSource) {
        return m_currentSource->availablePorts();
    }
    return {};
}

DataSource* DataSourceManager::currentSource() const {
    return m_currentSource;
}

QString DataSourceManager::currentMode() const {
    return m_currentMode;
}

QStringList DataSourceManager::availableModes() const {
    return m_sources.keys();
}