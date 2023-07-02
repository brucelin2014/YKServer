// 2023-02-26, Bruce

#include "ztserver_api_http.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QString>
#include <QDir>
#include "util/log.h"

ZTServer_api_Http::ZTServer_api_Http(IZTServer_api_Listener* pListener, QObject* parent)
    : QObject(parent)
    , m_host_url("")
    , m_request_url("")
    , m_httpClient(pListener, parent)
{

}

ZTServer_api_Http::~ZTServer_api_Http()
{
}

void ZTServer_api_Http::SetParentThread(QThread* pThread)
{
    if (pThread != nullptr)
        m_httpClient.SetParentThread(pThread);
}

// 1获取计划治疗方案
bool ZTServer_api_Http::getTreatPlan(const QString& deviceId, const QString& sysCode)
{
    m_request_url = m_host_url;
    m_request_url.append("/devices/getTreatPlan");
    m_request_url.append("?deviceId=");
    m_request_url.append(deviceId);
    m_request_url.append("&sysCode=");
    m_request_url.append(sysCode);

    Log::instance()->debug(QString("getTreatPlan: %1").arg(m_request_url).toUtf8());
    return m_httpClient.Get(m_request_url);
}

// 2提交设备治疗参数
bool ZTServer_api_Http::receiveDevicesData(const QByteArray& param)
{
    m_request_url = m_host_url;
    m_request_url.append("/devices/receiveDevicesData");

    Log::instance()->debug(QString("receiveDevicesData: %1").arg(m_request_url).toUtf8());
    Log::instance()->debug(param == nullptr ? "" : param);

    QByteArray array = param == nullptr ? "" : param;    //类型转换
    return m_httpClient.Post(m_request_url, array);
}

// 3同步设备状态
bool ZTServer_api_Http::syncStatus(const QString& deviceId, const QString& time, const QString& type)
{
    m_request_url = m_host_url;
    m_request_url.append("/devices/syncStatus");
    m_request_url.append("?deviceId=");
    m_request_url.append(deviceId);
    m_request_url.append("&time=");
    m_request_url.append(time);
    m_request_url.append("&type=");
    m_request_url.append(type);

    Log::instance()->debug(QString("syncStatus: %1").arg(m_request_url).toUtf8());
    return m_httpClient.Get(m_request_url);
}

// 4同步治疗状态: 1:开始治疗；2：结束治疗;3：拒绝治疗
bool ZTServer_api_Http::syncTreatStatus(const QString& deviceId, const QString& recordId, const QString& status, const QString& time)
{
    m_request_url = m_host_url;
    m_request_url.append("/devices/syncTreatStatus");
    m_request_url.append("?deviceId=");
    m_request_url.append(deviceId);
    m_request_url.append("&recordId=");
    m_request_url.append(recordId);
    m_request_url.append("&status=");
    m_request_url.append(status);
    m_request_url.append("&time=");
    m_request_url.append(time);

    Log::instance()->debug(QString("syncTreatStatus: %1").arg(m_request_url).toUtf8());
    return m_httpClient.Get(m_request_url);
}

// 5获取治疗状态（getTreatStatus - 数据下行）
bool ZTServer_api_Http::getTreatStatus(const QString& deviceId, const QString& recordId)
{
    m_request_url = m_host_url;
    m_request_url.append("/devices/getTreatStatus");
    m_request_url.append("?deviceId=");
    m_request_url.append(deviceId);
    m_request_url.append("&recordId=");
    m_request_url.append(recordId);

    Log::instance()->debug(QString("getTreatStatus: %1").arg(m_request_url).toUtf8());
    return m_httpClient.Get(m_request_url);
}


// 6提交治疗或评定报告
bool ZTServer_api_Http::submitReport(const QString& filePath, const QString& deviceid, const QString& patientID, const QString& recordId)
{
    m_request_url = m_host_url;
    m_request_url.append("/devices/submitReport");
    m_request_url.append("?deviceid=");
    m_request_url.append(deviceid);
    m_request_url.append("&patientID=");
    m_request_url.append(patientID);
    m_request_url.append("&recordId=");
    m_request_url.append(recordId);

    Log::instance()->debug(QString("submitReport: %1").arg(m_request_url).toUtf8());
    Log::instance()->debug(QString("submitReport: %1").arg(filePath).toUtf8());
    return m_httpClient.Post_PDF(m_request_url, filePath);
}

// 7治疗方案下发测试
bool ZTServer_api_Http::testData(const QString& deviceId)
{
    m_request_url = m_host_url;
    m_request_url.append("/devices/testData");
    m_request_url.append("?deviceId=");
    m_request_url.append(deviceId);

    Log::instance()->debug(QString("testData: %1").arg(m_request_url).toUtf8());
    return m_httpClient.Get(m_request_url);
}
