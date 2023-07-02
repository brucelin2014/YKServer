// 2023-02-27, Bruce

#ifndef ZTSERVICE_THREAD_H
#define ZTSERVICE_THREAD_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include "interface/IZTServer_api.h"
#include "entity/configobj.h"
#include "interface/IZTServer_api_Listener.h"

// 启动线程定时获取数据
class ZTService_Thread : public QThread
{
    Q_OBJECT
public:
    ZTService_Thread(QObject *parent, IZTServer_api_Listener* pListener, ConfigObj* pConfig);
    virtual ~ZTService_Thread();

    void stop();
    void pause();
    void resume();

private:
    void run();

private:
    IZTServer_api* m_pServer;
    ConfigObj* m_pConfig;

    volatile bool m_running;
    QMutex m_pauseLock;
};

#endif // ZTSERVICE_THREAD_H
