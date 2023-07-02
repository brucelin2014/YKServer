// 2023-03-03, Bruce

#ifndef ZTS_DEF_H
#define ZTS_DEF_H

#include <QString>

// 康复物联网API
enum ZTS_API
{
    API_getTreatPlan = 0,   // 获取计划治疗方案
    API_receiveDevicesData, // 提交设备治疗参数
    API_submitReport,       // 提交治疗或评定报告
    API_syncStatus,         // 同步设备状态
    API_syncTreatStatus,    // 同步治疗状态
    API_testData,           // 治疗方案下发测试
    API_error,
    API_getTreatStatus      // 获取治疗状态
};

ZTS_API GetApiType(const QString& url);

#endif // ZTS_DEF_H
