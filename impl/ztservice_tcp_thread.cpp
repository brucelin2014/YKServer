// 2023-03-10, Bruce

#include "ztservice_tcp_thread.h"
#include <windows.h>
#include "ztserver_api_http.h"

ZTService_Tcp_Thread::ZTService_Tcp_Thread(QObject *parent, IZTServer_api_Listener* pListener, ConfigObj* pConfig)
    : QThread(parent)
    , m_pServer(nullptr)
    , m_pConfig(pConfig)
    , m_running(true)
{
    m_pServer = new ZTServer_api_Http(pListener, this);
    if (m_pConfig != nullptr)
    {
        ((ZTServer_api_Http*)m_pServer)->SetParentThread(this);
        ((ZTServer_api_Http*)m_pServer)->Set_host_url(m_pConfig->Get_host_url());
    }
}

ZTService_Tcp_Thread::~ZTService_Tcp_Thread()
{
    m_pConfig = nullptr;
    if (m_pServer != nullptr)
    {
        delete m_pServer;
        m_pServer = nullptr;
    }

    stop();
}

void ZTService_Tcp_Thread::stop()
{
    m_running = false;
    quit();
    wait();
}

void ZTService_Tcp_Thread::pause()
{
    m_pauseLock.lock();
}

void ZTService_Tcp_Thread::resume()
{
    m_pauseLock.unlock();
}

void ZTService_Tcp_Thread::run()
{
    while (m_running)
    {
        m_pauseLock.lock();

        uint interval = 0;
        if (m_pConfig != nullptr)
            interval = m_pConfig->Get_data_interval();

        if (interval < 1)
            interval = 1000;
        Sleep(interval);

        if (m_pServer != nullptr && m_pConfig != nullptr)
            m_pServer->getTreatPlan(m_pConfig->Get_deviceId(), m_pConfig->Get_sysCode());

        m_pauseLock.unlock();
    }
}
