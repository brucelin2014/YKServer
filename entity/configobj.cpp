// 2023-02-26, Bruce

#include "configobj.h"

ConfigObj::ConfigObj()
    : m_host_url("")
    , m_deviceId("")
    , m_sysCode("")

    , m_param("")
    , m_patientID("")
    , m_recordId("")

    , m_getdata_interval(1000)
    , m_syncStatus_interval(3000)

    , m_report_folder("")
{

}
