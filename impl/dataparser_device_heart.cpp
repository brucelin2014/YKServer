// 2023-03-15, Bruce

#include "dataparser_device_heart.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QStringList>
#include <QDebug>
#include "entity/data_device_heart.h"
#include <QDateTime>

DataParser_Device_Heart::DataParser_Device_Heart()
{

}

// 解析设备发送TCP数据
// 解析心跳包
IDataBase_Device* DataParser_Device_Heart::ParseData(IDeviceStatus* pDeviceStatus, IConfig* pConfig, IZTServer_api* pZTServer_api, const QString& respond)
{
    Data_Device_Heart* pRes_a1s = nullptr;

    QJsonParseError jsonerror;
    QJsonDocument doc = QJsonDocument::fromJson(respond.toUtf8(), &jsonerror);
    if (!doc.isNull() && jsonerror.error == QJsonParseError::NoError)
    {
        if (doc.isObject())
        {
            pRes_a1s = new Data_Device_Heart();
            QJsonObject object = doc.object();
            QStringList list = object.keys();

            QJsonObject::iterator it = object.begin();
            while (it != object.end())
            {
                // 数据包格式
                if (it.key().compare("DataType", Qt::CaseInsensitive) == 0)
                    pRes_a1s->DataType = it.value().toInt();
                else if (it.key().compare("DeviceType", Qt::CaseInsensitive) == 0)
                    pRes_a1s->DeviceType = it.value().toString();
                else if (it.key().compare("DeviceMAC", Qt::CaseInsensitive) == 0)
                    pRes_a1s->DeviceMAC = it.value().toString();

                else if (it.key().compare("ScramStatus", Qt::CaseInsensitive) == 0)
                    pRes_a1s->ScramStatus = it.value().toInt();
                else if (it.key().compare("SpasmStatus", Qt::CaseInsensitive) == 0)
                    pRes_a1s->SpasmStatus = it.value().toInt();
                else if (it.key().compare("Status", Qt::CaseInsensitive) == 0)
                    pRes_a1s->Status = it.value().toInt();
                it++;
            }
        }
    }

    if (pRes_a1s != nullptr && pZTServer_api != nullptr && pDeviceStatus != nullptr)
    {
        pDeviceStatus->SyncDeviceStatus(pRes_a1s->Status == 1 ? STATUS_WORKING : STATUS_SLEEP);
    }
    return pRes_a1s;
}
