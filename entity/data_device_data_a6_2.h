// 2023-06-13, Bruce

#ifndef DATA_DEVICE_DATA_A6_2_H
#define DATA_DEVICE_DATA_A6_2_H

#include <QObject>
#include "interface/IDataBase_Device.h"
#include "database_device.h"


// 康复设备连接平台数据, A6_2, A6_2S
class Data_Device_Data_A6_2
        : public DataBase_Device
{
    Q_OBJECT
public:
    Data_Device_Data_A6_2();

    /// <summary>
    /// 运动状态
    /// 0-空闲
    /// 1-运动中
    /// 2-暂停
    /// 3-急停
    /// </summary>
    int Status;

    QString patientName;
    QString patientId;
    QString sex;
    QString age;

    QString recordId;

    QByteArray ToJson();
};

#endif // DATA_DEVICE_DATA_A6_2_H
