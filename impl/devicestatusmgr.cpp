// 2023-03-15, Bruce

#include "devicestatusmgr.h"

DeviceStatusMgr::DeviceStatusMgr()
    : m_Status(STATUS_OFF)
    , m_TimeoutSec(10) // 10秒超时
    , m_Counter(0)
    , m_pTimer(new QTimer(this))
{
    StartTimer();
}

DeviceStatusMgr::~DeviceStatusMgr()
{
    m_pTimer->stop();
    delete m_pTimer;
}

// 更新设备状态
void DeviceStatusMgr::SyncDeviceStatus(DEVICE_STATUS status)
{
    m_Status = status;
    if (status != STATUS_OFF)
        m_Counter = 0;
}

bool DeviceStatusMgr::IsTimeout()
{
    if (m_Counter > m_TimeoutSec)
        return true;
    return false;
}


void DeviceStatusMgr::StartTimer()
{
    connect(m_pTimer, &QTimer::timeout, this, &DeviceStatusMgr::OnTimeout);
    m_pTimer->start(1000);
}

void DeviceStatusMgr::OnTimeout()
{
    m_Counter++;
    if (m_Counter > 65535)
        m_Counter = m_TimeoutSec + 1;

    if (m_Counter > m_TimeoutSec) // 超时离线
        m_Status = STATUS_OFF;
    else
    {
        if (m_Status == STATUS_OFF) // 只有刚开机的时候，第一次请求这个接口的时候是开机，然后后面再次同步就是2，治疗中就是3
            m_Status = STATUS_ON;
    }
}
