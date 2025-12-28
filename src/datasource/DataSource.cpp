#include "DataSource.h"
#include "DataHub.h"

DataSource::DataSource(DataHub* dataHub, QObject *parent) 
    : QObject(parent), m_dataHub(dataHub) {}