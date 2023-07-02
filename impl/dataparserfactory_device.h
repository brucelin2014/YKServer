// 2023-04-12, Bruce

#ifndef DATAPARSERFACTORY_DEVICE_H
#define DATAPARSERFACTORY_DEVICE_H

#include "interface/IDataParser_Device.h"

// 解析设备发送TCP数据
class DataParserFactory_Device
{
public:
    DataParserFactory_Device();

    // 解析设备发送TCP数据
    static IDataParser_Device* CreateDataParser(const QString& sysCode, const int& dataType);
};

#endif // DATAPARSERFACTORY_DEVICE_H
