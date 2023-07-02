// 2023-03-06, Bruce

#include "ztservice_syncStatus_thread.h"
#include <windows.h>
#include <QDateTime>
#include "ztserver_api_http.h"

ZTService_syncStatus_Thread::ZTService_syncStatus_Thread(QObject *parent, IZTServer_api_Listener* pListener, ConfigObj* pConfig, IDeviceStatus* pDeviceStatus)
    : QThread(parent)
    , m_pServer(nullptr)
    , m_pConfig(pConfig)
    , m_pDeviceStatus(pDeviceStatus)
    , m_running(true)
{
    m_pServer = new ZTServer_api_Http(pListener, this);
    if (m_pConfig != nullptr)
    {
        ((ZTServer_api_Http*)m_pServer)->SetParentThread(this);
        ((ZTServer_api_Http*)m_pServer)->Set_host_url(m_pConfig->Get_host_url());
    }
}

ZTService_syncStatus_Thread::~ZTService_syncStatus_Thread()
{
    m_pConfig = nullptr;
    if (m_pServer != nullptr)
    {
        delete m_pServer;
        m_pServer = nullptr;
    }

    stop();
}

void ZTService_syncStatus_Thread::stop()
{
    m_running = false;
    quit();
    wait();
}

void ZTService_syncStatus_Thread::pause()
{
    m_pauseLock.lock();
}

void ZTService_syncStatus_Thread::resume()
{
    m_pauseLock.unlock();
}

void ZTService_syncStatus_Thread::run()
{
    QDateTime time;
    while (m_running)
    {
        m_pauseLock.lock();

        uint interval = 0;
        if (m_pConfig != nullptr)
            interval = m_pConfig->Get_syncStatus_interval();

        if (interval < 1)
            interval = 3000;
        Sleep(interval);

        if (m_pServer != nullptr && m_pConfig != nullptr && m_pDeviceStatus != nullptr)
        {
            // 设备状态（1(开机);2(待机);3(治疗中);4(离线)）
            // 只有刚开机的时候，第一次请求这个接口的时候是开机，然后后面再次同步就是2，治疗中就是3
            m_pServer->syncStatus(m_pConfig->Get_deviceId()
                                  , time.currentDateTime().toString("yyyy-MM-dd hh:mm:ss")
                                  , QString("%1").arg(m_pDeviceStatus->GetStatus()));
        }

        m_pauseLock.unlock();
    }
}
