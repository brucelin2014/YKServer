// 2023-02-26, Bruce

#ifndef IZTSERVER_H
#define IZTSERVER_H

#include <QString>

class IZTServer_api
{
public:
    virtual ~IZTServer_api() {}

    // 1获取计划治疗方案
    virtual bool getTreatPlan(const QString& deviceId, const QString& sysCode) = 0;

    // 2提交设备治疗参数
    virtual bool receiveDevicesData(const QByteArray& param) = 0;

    // 3同步设备状态:设备状态（1(开机);2(待机);3(治疗中);4(离线)）
    // 只有刚开机的时候，第一次请求这个接口的时候是开机，然后后面再次同步就是2，治疗中就是3
    virtual bool syncStatus(const QString& deviceId, const QString& time, const QString& type) = 0;

    // 4同步治疗状态: 1:开始治疗；2：结束治疗;3：拒绝治疗
    virtual bool syncTreatStatus(const QString& deviceId, const QString& recordId, const QString& status, const QString& time) = 0;

    // 5获取治疗状态（getTreatStatus - 数据下行）
    virtual bool getTreatStatus(const QString& deviceId, const QString& recordId) = 0;

    // 6提交治疗或评定报告
    virtual bool submitReport(const QString& filePath, const QString& deviceid, const QString& patientID, const QString& recordId) = 0;

    // 7治疗方案下发测试
    virtual bool testData(const QString& deviceId) = 0;
};

#endif // IZTSERVER_H
