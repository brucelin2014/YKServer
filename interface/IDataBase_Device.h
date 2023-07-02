// 2023-03-15, Bruce

#ifndef IDATABASE_DEVICE_H
#define IDATABASE_DEVICE_H

#include <QString>
#include <QObject>

class IDataBase_Device : public QObject
{
public:
    virtual ~IDataBase_Device() {}

    // 1	康复设备发送心跳包数据 –ZTServer回复:101
    // 2	康复设备上传实时信息   –ZTServer回复:102
    // 3	康复设备接收控制指令   –设备回复:103
    // 4	康复设备上传报告数据   –ZTServer回复:104
    // 5	指令回复
    virtual int GetDataType() = 0;

    virtual QString GetDeviceType() = 0;

    virtual QString GetDeviceMAC() = 0;

    virtual QByteArray ToJson() = 0;
};

#endif // IDATABASE_DEVICE_H
