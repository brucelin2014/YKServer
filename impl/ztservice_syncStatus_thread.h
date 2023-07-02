// 2023-03-06, Bruce

#ifndef ZTSERVICE_SYNCSTATUS_THREAD_H
#define ZTSERVICE_SYNCSTATUS_THREAD_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include "interface/IZTServer_api.h"
#include "entity/configobj.h"
#include "interface/IZTServer_api_Listener.h"
#include "interface/IDeviceStatus.h"

// 启动线程定时同步设备状态
class ZTService_syncStatus_Thread : public QThread
{
    Q_OBJECT
public:
    ZTService_syncStatus_Thread(QObject *parent, IZTServer_api_Listener* pListener, ConfigObj* pConfig, IDeviceStatus* pDeviceStatus);
    virtual ~ZTService_syncStatus_Thread();

    void stop();
    void pause();
    void resume();

private:
    void run();

private:
    IZTServer_api* m_pServer;
    ConfigObj* m_pConfig;
    IDeviceStatus* m_pDeviceStatus;

    volatile bool m_running;
    QMutex m_pauseLock;
};

#endif // ZTSERVICE_SYNCSTATUS_THREAD_H
