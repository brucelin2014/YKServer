// 2023-03-15, Bruce

#include "dataparser_device_respond.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QStringList>
#include <QDebug>
#include "entity/data_device_respond.h"

DataParser_Device_Respond::DataParser_Device_Respond()
{

}

// 解析设备发送TCP数据
IDataBase_Device* DataParser_Device_Respond::ParseData(IDeviceStatus* pDeviceStatus, IConfig* pConfig, IZTServer_api* pZTServer_api, const QString& respond)
{
    Data_Device_Respond* pRes_a1s = nullptr;

    QJsonParseError jsonerror;
    QJsonDocument doc = QJsonDocument::fromJson(respond.toUtf8(), &jsonerror);
    if (!doc.isNull() && jsonerror.error == QJsonParseError::NoError)
    {
        if (doc.isObject())
        {
            pRes_a1s = new Data_Device_Respond();
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

                else if (it.key().compare("Code", Qt::CaseInsensitive) == 0)
                    pRes_a1s->Code = it.value().toInt();
                else if (it.key().compare("Msg", Qt::CaseInsensitive) == 0)
                    pRes_a1s->Msg = it.value().toString();
                it++;
            }
        }
    }
    return pRes_a1s;
}
