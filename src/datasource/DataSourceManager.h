#pragma once

#include <QObject>
#include <QMap>
#include "DataSource.h"

class DataSourceManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(DataSource* currentSource READ currentSource NOTIFY currentSourceChanged)
    Q_PROPERTY(QString currentMode READ currentMode NOTIFY currentModeChanged)
    Q_PROPERTY(QStringList availableModes READ availableModes NOTIFY modesChanged)

public:
    explicit DataSourceManager(QObject *parent = nullptr);

    void registerSource(const QString &name, DataSource* source);
    Q_INVOKABLE void setMode(const QString &mode);
    Q_INVOKABLE bool connectSource(const QVariantMap &settings);
    Q_INVOKABLE void disconnectSource();
    Q_INVOKABLE void sendData(const QString &data);
    Q_INVOKABLE QStringList availablePorts();
    DataSource* currentSource() const;
    QString currentMode() const;
    QStringList availableModes() const;

signals:
    void currentSourceChanged();
    void currentModeChanged();
    void modesChanged();

private:
    QMap<QString, DataSource*> m_sources;
    DataSource* m_currentSource = nullptr;
    QString m_currentMode;
};