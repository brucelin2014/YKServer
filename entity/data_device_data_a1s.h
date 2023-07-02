// 2023-03-15, Bruce

#ifndef DATA_DEVICE_DATA_A1S_H
#define DATA_DEVICE_DATA_A1S_H

#include <QObject>
#include "interface/IDataBase_Device.h"
#include "database_device.h"


// 康复设备连接平台数据
class Data_Device_Data_A1S
        : public DataBase_Device
{
    Q_OBJECT
public:
    Data_Device_Data_A1S();

    /// <summary>
    /// 运动状态
    /// 0-空闲
    /// 1-运动中
    /// 2-暂停
    /// 3-急停
    /// </summary>
    int Status;

    /// <summary>
    /// 当前转速
    /// </summary>
    int VelocityCur;

    /// <summary>
    /// 治疗时间
    /// </summary>
    int Duration;

    int AngleFromLeft;
    int AngleToLeft;
    int AngleFromRight;
    int AngleToRight;

    QString patientName;
    QString patientId;
    QString sex;
    QString age;

    QString recordId;

    QByteArray ToJson();
};

#endif // DATA_DEVICE_DATA_A1S_H
