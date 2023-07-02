// 2023-03-10, Bruce

#ifndef ZTSERVICE_TCP_THREAD_H
#define ZTSERVICE_TCP_THREAD_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include "interface/IZTServer_api.h"
#include "entity/configobj.h"
#include "interface/IZTServer_api_Listener.h"

// 线程收发数据
class ZTService_Tcp_Thread : public QThread
{
    Q_OBJECT
public:
    ZTService_Tcp_Thread(QObject *parent, IZTServer_api_Listener* pListener, ConfigObj* pConfig);
    virtual ~ZTService_Tcp_Thread();

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

    // 接收数据队列
    QList<QByteArray> m_rev;
};

#endif // ZTSERVICE_TCP_THREAD_H
