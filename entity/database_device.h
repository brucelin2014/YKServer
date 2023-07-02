// 2023-03-15, Bruce

#ifndef DATABASE_DEVICE_H
#define DATABASE_DEVICE_H

#include <QObject>
#include "interface/IDataBase_Device.h"

// 康复设备连接平台数据
class DataBase_Device
        : public IDataBase_Device
{
    Q_OBJECT
public:
    DataBase_Device();

    // 1	康复设备发送心跳包数据 –ZTServer回复:101
    // 2	康复设备上传实时信息   –ZTServer回复:102
    // 3	康复设备接收控制指令   –设备回复:103
    // 4	康复设备上传报告数据   –ZTServer回复:104
    // 5	指令回复
    virtual int GetDataType() override { return DataType; }

    virtual QString GetDeviceType() override { return DeviceType; }

    virtual QString GetDeviceMAC() override { return DeviceMAC; }

    virtual QByteArray ToJson() override { return ""; }

    /// <summary>
    /// 数据类型:
    /// 1-康复设备发送心跳包数据–ZTServer回复:101
    /// 2-康复设备上传实时信息–ZTServer回复:102
    /// 3-康复设备接收控制指令–设备回复:103
    /// 4-康复设备上传报告数据–ZTServer回复:104
    /// 5-指令回复
    /// </summary>
    int DataType = 0;

    // 设备类型
    QString DeviceType = "";

    // 设备唯一标记
    QString DeviceMAC = "";
};

#endif // DATABASE_DEVICE_H
