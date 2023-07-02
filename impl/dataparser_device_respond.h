// 2023-03-15, Bruce

#ifndef DATAPARSER_DEVICE_RESPOND_H
#define DATAPARSER_DEVICE_RESPOND_H

#include "interface/IDataParser_Device.h"
#include "interface/IZTServer_api.h"
#include "interface/IConfig.h"
#include "interface/IDeviceStatus.h"

// 解析设备发送TCP数据
class DataParser_Device_Respond : public IDataParser_Device
{
public:
    DataParser_Device_Respond();

    virtual IDataBase_Device* ParseData(IDeviceStatus* pDeviceStatus, IConfig* pConfig, IZTServer_api* pZTServer_api, const QString& respond) override;

private:
    IZTServer_api* m_pZTServer_api;
};

#endif // DATAPARSER_DEVICE_RESPOND_H
