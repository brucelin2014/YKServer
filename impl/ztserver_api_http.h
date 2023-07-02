// 2023-02-26, Bruce

#ifndef ZTSERVER_API_HTTP_H
#define ZTSERVER_API_HTTP_H

#include <QObject>
#include "interface/IZTServer_api.h"
#include "interface/IZTServer_api_Listener.h"
#include "util/httpclient.h"

class ZTServer_api_Http
        : public QObject
        , public IZTServer_api
{
    Q_OBJECT

public:
    ZTServer_api_Http(IZTServer_api_Listener* pListener, QObject* parent);
    ~ZTServer_api_Http();


    // 1获取计划治疗方案
    virtual bool getTreatPlan(const QString& deviceId, const QString& sysCode) override;

    // 2提交设备治疗参数
    virtual bool receiveDevicesData(const QByteArray& param) override;

    // 3同步设备状态
    virtual bool syncStatus(const QString& deviceId, const QString& time, const QString& type) override;

    // 4同步治疗状态
    virtual bool syncTreatStatus(const QString& deviceId, const QString& recordId, const QString& status, const QString& time) override;

    // 5获取治疗状态（getTreatStatus - 数据下行）
    bool getTreatStatus(const QString& deviceId, const QString& recordId) override;

    // 6提交治疗或评定报告
    virtual bool submitReport(const QString& filePath, const QString& deviceid, const QString& patientID, const QString& recordId) override;

    // 7治疗方案下发测试
    virtual bool testData(const QString& deviceId) override;

    void Set_host_url(const QString& host_url) { m_host_url = host_url; }
    const QString& GetRequestUrl() { return m_request_url; }
    void SetParentThread(QThread* pThread);

private:
    QString m_host_url;
    QString m_request_url;

    HttpClient m_httpClient;

    QString getTime();
    bool WriteLog(const QByteArray& content);
};

#endif // ZTSERVER_API_HTTP_H
