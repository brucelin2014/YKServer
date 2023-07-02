// 2023-03-15, Bruce

#ifndef IDEVICE_STATUS_H
#define IDEVICE_STATUS_H

#include <QString>

enum DEVICE_STATUS
{
    STATUS_ON = 1,  // 开机
    STATUS_SLEEP,   // 待机
    STATUS_WORKING, // 治疗中
    STATUS_OFF      // 离线
};

class IDeviceStatus
{
public:
    virtual ~IDeviceStatus() {}

    // 设备状态（1(开机);2(待机);3(治疗中);4(离线)）
    // 只有刚开机的时候，第一次请求这个接口的时候是开机，然后后面再次同步就是2，治疗中就是3
    virtual DEVICE_STATUS GetStatus() = 0;

    // 更新设备状态
    virtual void SyncDeviceStatus(DEVICE_STATUS status) = 0;
};

#endif // IRESPONDDATA_H
