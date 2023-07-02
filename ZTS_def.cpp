// 2023-03-03, Bruce

#include "ZTS_def.h"

ZTS_API GetApiType(const QString& url)
{
    if (url.indexOf("getTreatPlan") > 0)
        return API_getTreatPlan;
    else if (url.indexOf("receiveDevicesData") > 0)
        return  API_receiveDevicesData;
    else if (url.indexOf("submitReport") > 0)
        return API_submitReport;
    else if (url.indexOf("syncStatus") > 0)
        return API_syncStatus;
    else if (url.indexOf("syncTreatStatus") > 0)
        return API_syncTreatStatus;
    else if (url.indexOf("testData") > 0)
        return API_testData;
    else if (url.indexOf("getTreatStatus") > 0)
        return API_getTreatStatus;
    return API_error;
}
