// 2023-03-15, Bruce

#ifndef DEVICESTATUSMGR_H
#define DEVICESTATUSMGR_H

#include "interface/IDeviceStatus.h"
#include <QObject>
#include <memory>
#include <QTimer>

class DeviceStatusMgr
        : public IDeviceStatus
        , public QObject

{
public:
    DeviceStatusMgr();
    virtual ~DeviceStatusMgr();

    // 设备状态（1(开机);2(待机);3(治疗中);4(离线)）
    virtual DEVICE_STATUS GetStatus() override { return m_Status; }

    // 更新设备状态
    virtual void SyncDeviceStatus(DEVICE_STATUS status) override;

    void SetTimeoutSec(const uint& timeoutSec) { m_TimeoutSec = timeoutSec; }

private:
    DEVICE_STATUS m_Status; // 只有刚开机的时候，第一次请求这个接口的时候是开机，然后后面再次同步就是2，治疗中就是3
    uint m_TimeoutSec; // 超时（秒）
    uint m_Counter;
    QTimer* m_pTimer;

    bool IsTimeout();
    void StartTimer();
    void OnTimeout();
};

#endif // DEVICESTATUSMGR_H
