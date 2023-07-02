// 2023-03-15, Bruce

#ifndef DATA_DEVICE_REPORT_H
#define DATA_DEVICE_REPORT_H

#include <QObject>
#include "interface/IDataBase_Device.h"
#include "database_device.h"

// 康复设备连接平台数据
class Data_Device_Report
        : public DataBase_Device
{
    Q_OBJECT
public:
    Data_Device_Report();

    /// <summary>
    /// 方案编号
    /// </summary>
    QString recordId;

    /// <summary>
    /// 年龄
    /// </summary>
    QString age;

    /// <summary>
    /// 用户编号
    /// </summary>
    QString patientId;

    /// <summary>
    /// 性别 0-女, 1-男
    /// </summary>
    QString sex;

    /// <summary>
    /// 用户
    /// </summary>
    QString patientName;

    /// <summary>
    /// Pdf报告文件名
    /// </summary>
    QString PdfFileName;
};

#endif // DATA_DEVICE_REPORT_H
