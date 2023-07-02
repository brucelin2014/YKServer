// 2023-06-16, Bruce

#ifndef DATAPARSER_A3_2_DEVICE_DATA_H
#define DATAPARSER_A3_2_DEVICE_DATA_H

#include "interface/IDataParser_Device.h"
#include "interface/IZTServer_api.h"
#include "interface/IConfig.h"
#include "interface/IDeviceStatus.h"

// 解析设备发送TCP数据
class DataParser_A3_2_Device_Data
        : public IDataParser_Device
{
public:
    DataParser_A3_2_Device_Data();

    virtual IDataBase_Device* ParseData(IDeviceStatus* pDeviceStatus, IConfig* pConfig, IZTServer_api* pZTServer_api, const QString& respond) override;
};

#endif // DATAPARSER_A3_2_DEVICE_DATA_H
