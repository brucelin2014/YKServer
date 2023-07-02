// 2023-03-15, Bruce

#include "dataparserfactory_device.h"
#include "dataparserfactory_device_a1s.h"
#include "dataparserfactory_device_sl4.h"
#include "dataparserfactory_device_a1.h"
#include "dataparserfactory_device_a3_2.h"
#include "dataparserfactory_device_a6_2.h"
#include "dataparserfactory_device_a8.h"
#include "dataparserfactory_device_ps1.h"

DataParserFactory_Device::DataParserFactory_Device()
{

}

// 解析设备发送TCP数据
IDataParser_Device* DataParserFactory_Device::CreateDataParser(const QString& sysCode, const int& dataType)
{
    if (sysCode == "YKA1S")
        return DataParserFactory_Device_A1S::CreateDataParser(dataType);
    else if (sysCode == "YKSL4" || sysCode == "YKSL4I" || sysCode == "YKSL4I-2")
        return DataParserFactory_Device_SL4::CreateDataParser(dataType);
    else if (sysCode == "YKA1" || sysCode == "YKA1-3S" || sysCode == "YKA1-3")
        return DataParserFactory_Device_A1::CreateDataParser(dataType);
    else if (sysCode == "YKA3-2" || sysCode == "YKA3-2S")
        return DataParserFactory_Device_A3_2::CreateDataParser(dataType);
    else if (sysCode == "YKA6-2" || sysCode == "YKA6-2S")
        return DataParserFactory_Device_A6_2::CreateDataParser(dataType);
    else if (sysCode == "YKA8" || sysCode == "YKA8-3")
        return DataParserFactory_Device_A8::CreateDataParser(dataType);
    else if (sysCode == "YKPS1" || sysCode == "YKPS2")
        return DataParserFactory_Device_PS1::CreateDataParser(dataType);
    return nullptr;
}
