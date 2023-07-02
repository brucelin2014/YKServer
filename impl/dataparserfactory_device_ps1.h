// 2023-06-16, Bruce

#ifndef DATAPARSERFACTORY_DEVICE_PS1_H
#define DATAPARSERFACTORY_DEVICE_PS1_H

#include "interface/IDataParser_Device.h"

// 解析设备发送TCP数据
class DataParserFactory_Device_PS1
{
public:
    DataParserFactory_Device_PS1();

    // 1	康复设备发送心跳包数据 –ZTServer回复:101
    // 2	康复设备上传实时信息   –ZTServer回复:102
    // 3	康复设备接收控制指令   –设备回复:103
    // 4	康复设备上传报告数据   –ZTServer回复:104
    // 5	指令回复
    static IDataParser_Device* CreateDataParser(const int& dataType);
};

#endif // DATAPARSERFACTORY_DEVICE_H
