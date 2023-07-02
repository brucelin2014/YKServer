// 2023-02-26, Bruce

#include "configimpl.h"
#include <QCoreApplication>

ConfigImpl::ConfigImpl()
    : m_pSettings(nullptr)
{
    QString currPath = QCoreApplication::applicationDirPath() + "/ZTServer_config.ini";
    m_pSettings = new QSettings (currPath, QSettings::IniFormat);
}

ConfigImpl::~ConfigImpl()
{
    delete m_pSettings;
    m_pSettings = nullptr;
}

void ConfigImpl::Load()
{
    m_ConfigObj.Set_host_url(m_pSettings->value("/sys/host_url").toString());
    m_ConfigObj.Set_deviceId(m_pSettings->value("/sys/deviceId").toString());
    m_ConfigObj.Set_sysCode(m_pSettings->value("/sys/sysCode").toString());

    m_ConfigObj.Set_data_interval(m_pSettings->value("/sys/getdata_interval").toUInt());
    m_ConfigObj.Set_syncStatus_interval(m_pSettings->value("/sys/syncStatus_interval").toUInt());

    m_ConfigObj.Set_report_folder(m_pSettings->value("/sys/report_folder").toString());
}
