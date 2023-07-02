// 2023-04-12, Bruce

#include "dataparser_sl4_device_data.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QStringList>
#include <QDebug>
#include "entity/data_device_data_sl4.h"
#include "entity/respondobj_sl4.h"
#include <QDateTime>

DataParser_SL4_Device_Data::DataParser_SL4_Device_Data()
{

}

// 解析设备发送TCP数据
// 康复设备上传实时信息
IDataBase_Device* DataParser_SL4_Device_Data::ParseData(IDeviceStatus* pDeviceStatus, IConfig* pConfig, IZTServer_api* pZTServer_api, const QString& respond)
{
    Data_Device_Data_SL4* pRes_sl4 = nullptr;

    QJsonParseError jsonerror;
    QJsonDocument doc = QJsonDocument::fromJson(respond.toUtf8(), &jsonerror);
    if (!doc.isNull() && jsonerror.error == QJsonParseError::NoError)
    {
        if (doc.isObject())
        {
            pRes_sl4 = new Data_Device_Data_SL4();
            QJsonObject object = doc.object();
            QStringList list = object.keys();

            QJsonObject::iterator it = object.begin();
            while (it != object.end())
            {
                // 数据包格式
                if (it.key().compare("DataType", Qt::CaseInsensitive) == 0)
                    pRes_sl4->DataType = it.value().toInt();
                else if (it.key().compare("DeviceType", Qt::CaseInsensitive) == 0)
                    pRes_sl4->DeviceType = it.value().toString();
                else if (it.key().compare("DeviceMAC", Qt::CaseInsensitive) == 0)
                    pRes_sl4->DeviceMAC = it.value().toString();

                else if (it.key().compare("Status", Qt::CaseInsensitive) == 0)
                    pRes_sl4->Status = it.value().toInt();
                else if (it.key().compare("Mode", Qt::CaseInsensitive) == 0)
                    pRes_sl4->Mode = it.value().toInt();
                else if (it.key().compare("Content", Qt::CaseInsensitive) == 0)
                    pRes_sl4->Content = it.value().toInt();
                else if (it.key().compare("Body", Qt::CaseInsensitive) == 0)
                    pRes_sl4->Body  = it.value().toInt();

                else if (it.key().compare("patientName", Qt::CaseInsensitive) == 0)
                    pRes_sl4->patientName = it.value().toString();
                else if (it.key().compare("patientId", Qt::CaseInsensitive) == 0)
                    pRes_sl4->patientId = it.value().toString();
                else if (it.key().compare("sex", Qt::CaseInsensitive) == 0)
                    pRes_sl4->sex = it.value().toString();
                else if (it.key().compare("age", Qt::CaseInsensitive) == 0)
                    pRes_sl4->age = it.value().toString();
                else if (it.key().compare("recordId", Qt::CaseInsensitive) == 0)
                    pRes_sl4->recordId = it.value().toString();
                it++;
            }
        }
    }

    if (pRes_sl4 != nullptr && pZTServer_api != nullptr && pConfig != nullptr)
    {
        RespondObj_SL4 sl4Data;
        sl4Data.obj.deviceId = pConfig->Get_deviceId();
        sl4Data.obj.recordId = pRes_sl4->recordId;

        sl4Data.obj.patientId = pRes_sl4->patientId;
        sl4Data.obj.patientName = pRes_sl4->patientName;
        sl4Data.obj.sex = pRes_sl4->sex;
        sl4Data.obj.age = pRes_sl4->age;

        sl4Data.obj.Mode = pRes_sl4->Mode;
        sl4Data.obj.Content = pRes_sl4->Content;
        sl4Data.obj.Body = pRes_sl4->Body;

        // 提交设备治疗参数
        pZTServer_api->receiveDevicesData(sl4Data.ToJson());

        /// <summary>
        /// 运动状态
        /// 0-空闲
        /// 1-运动中
        /// 2-暂停
        /// 3-急停
        /// </summary>
        if (pRes_sl4->Status == 1 || pRes_sl4->Status == 2)
        {
            // 同步治疗状态: 1:开始治疗；2：结束治疗;3：拒绝治疗
            QDateTime time;
            QString status = QString::number(pRes_sl4->Status);
            pZTServer_api->syncTreatStatus(pConfig->Get_deviceId(), pRes_sl4->recordId, status
                                           , time.currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        }
    }
    return pRes_sl4;
}
