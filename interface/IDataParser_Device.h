// 2023-03-15, Bruce

#ifndef IDATAPARSER_DEVICE_H
#define IDATAPARSER_DEVICE_H

#include <QString>
#include "ZTS_def.h"
#include "IDataBase_Device.h"
#include "IZTServer_api.h"
#include "IConfig.h"
#include "IDeviceStatus.h"

class IDataParser_Device
{
public:
    virtual ~IDataParser_Device() {}

    virtual IDataBase_Device* ParseData(IDeviceStatus* pDeviceStatus, IConfig* pConfig, IZTServer_api* pZTServer_api, const QString& respond) = 0;
};

#endif // IDATAPARSER_H
