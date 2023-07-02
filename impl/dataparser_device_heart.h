// 2023-03-15, Bruce

#ifndef DATAPARSER_DEVICE_HEART_H
#define DATAPARSER_DEVICE_HEART_H

#include "interface/IDataParser_Device.h"
#include "interface/IZTServer_api.h"
#include "interface/IConfig.h"
#include "interface/IDeviceStatus.h"

// 解析设备发送TCP数据
class DataParser_Device_Heart : public IDataParser_Device
{
public:
    DataParser_Device_Heart();

    virtual IDataBase_Device* ParseData(IDeviceStatus* pDeviceStatus, IConfig* pConfig, IZTServer_api* pZTServer_api, const QString& respond) override;
};

#endif // DATAPARSER_DEVICE_HEART_H
