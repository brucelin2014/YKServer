// 2023-02-26, Bruce

#ifndef CONFIGIMPL_H
#define CONFIGIMPL_H

#include <QSettings>
#include "entity/configobj.h"
#include "interface/IConfig.h"

class ConfigImpl : public IConfig
{
public:
    ConfigImpl();
    virtual ~ConfigImpl();

    void Load();

    const QString& Get_host_url() { return m_ConfigObj.Get_host_url(); }
    virtual const QString& Get_deviceId() override { return m_ConfigObj.Get_deviceId(); }
    const QString& Get_sysCode() { return m_ConfigObj.Get_sysCode(); }

    const uint& Get_data_interval() { return m_ConfigObj.Get_data_interval(); }
    const uint& Get_syncStatus_interval() { return m_ConfigObj.Get_syncStatus_interval(); }

    virtual const QString& Get_report_folder() override { return m_ConfigObj.Get_report_folder(); }

private:
    QSettings* m_pSettings;

public:
    ConfigObj m_ConfigObj;
};

#endif // CONFIGIMPL_H
