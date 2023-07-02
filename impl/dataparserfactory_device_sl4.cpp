// 2023-04-12, Bruce

#include "dataparserfactory_device_sl4.h"
#include "dataparser_device_heart.h"
#include "dataparser_sl4_device_data.h"
#include "dataparser_device_report.h"
#include "dataparser_device_respond.h"

DataParserFactory_Device_SL4::DataParserFactory_Device_SL4()
{

}

// 解析设备发送TCP数据
// 1	康复设备发送心跳包数据 –ZTServer回复:101
// 2	康复设备上传实时信息   –ZTServer回复:102
// 3	康复设备接收控制指令   –设备回复:103
// 4	康复设备上传报告数据   –ZTServer回复:104
// 5	指令回复
IDataParser_Device* DataParserFactory_Device_SL4::CreateDataParser(const int& dataType)
{
    switch (dataType)
    {
    case 1:
        return new DataParser_Device_Heart();
    case 2:
        return new DataParser_SL4_Device_Data();
    case 3:
        return nullptr;
    case 4:
        return new DataParser_Device_Report();
    case 101:
    case 103:
        return new DataParser_Device_Respond();
    }
    return nullptr;
}
