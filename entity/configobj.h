// 2023-02-26, Bruce

#ifndef CONFIGOBJ_H
#define CONFIGOBJ_H

#include <QString>

class ConfigObj
{
public:
    ConfigObj();

    void Set_host_url(const QString& host_url) { m_host_url = host_url; }
    const QString& Get_host_url() { return m_host_url; }

    void Set_deviceId(const QString& deviceId) { m_deviceId = deviceId; }
    const QString& Get_deviceId() { return m_deviceId; }

    void Set_sysCode(const QString& sysCode) { m_sysCode = sysCode; }
    const QString& Get_sysCode() { return m_sysCode; }

    void Set_data_interval(const uint& data_interval) { m_getdata_interval = data_interval; }
    const uint& Get_data_interval() { return m_getdata_interval; }

    void Set_syncStatus_interval(const uint& syncStatus_interval) { m_syncStatus_interval = syncStatus_interval; }
    const uint& Get_syncStatus_interval() { return m_syncStatus_interval; }

    void Set_report_folder(const QString& report_folder) { m_report_folder = report_folder; }
    const QString& Get_report_folder() { return m_report_folder; }

    // 2023-06-30, Bruce
    void Set_recordId(const QString& recordId) { m_recordId = recordId; }
    const QString& Get_recordId() { return m_recordId; }
    //

private:
    QString m_host_url;  // 中天服务器链接
    QString m_deviceId;  // 设备唯一编码（设备ID/设备编码）
    QString m_sysCode;   // 设备厂商编码

    QString m_param;     // 提交的设备治疗最终参数，包括设备ID，治疗记录ID等，返回数据格式同下发计划治疗方案
    QString m_patientID; // 患者唯一标识（患者ID/个人ID）
    QString m_recordId;  // 患者治疗项目的唯一标识（治疗记录ID）

    uint m_getdata_interval;    // 定时获取数据间隔（毫秒）
    uint m_syncStatus_interval; // 定时同步设备状态间隔（毫秒）

    QString m_report_folder;    // pdf报告文件夹
};

#endif // CONFIGOBJ_H
