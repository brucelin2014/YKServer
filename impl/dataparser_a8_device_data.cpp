// 2023-06-15, Bruce

#include "dataparser_a8_device_data.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QStringList>
#include <QDebug>
#include "entity/data_device_data_a8.h"
#include "entity/respondobj_a8.h"
#include <QDateTime>

DataParser_A8_Device_Data::DataParser_A8_Device_Data()
{

}

// 解析设备发送TCP数据
// 康复设备上传实时信息
IDataBase_Device* DataParser_A8_Device_Data::ParseData(IDeviceStatus* pDeviceStatus, IConfig* pConfig, IZTServer_api* pZTServer_api, const QString& respond)
{
    Data_Device_Data_A8* pRes_A8 = nullptr;

    QJsonParseError jsonerror;
    QJsonDocument doc = QJsonDocument::fromJson(respond.toUtf8(), &jsonerror);
    if (!doc.isNull() && jsonerror.error == QJsonParseError::NoError)
    {
        if (doc.isObject())
        {
            pRes_A8 = new Data_Device_Data_A8();
            QJsonObject object = doc.object();
            QStringList list = object.keys();

            QJsonObject::iterator it = object.begin();
            while (it != object.end())
            {
                // 数据包格式
                if (it.key().compare("DataType", Qt::CaseInsensitive) == 0)
                    pRes_A8->DataType = it.value().toInt();
                else if (it.key().compare("DeviceType", Qt::CaseInsensitive) == 0)
                    pRes_A8->DeviceType = it.value().toString();
                else if (it.key().compare("DeviceMAC", Qt::CaseInsensitive) == 0)
                    pRes_A8->DeviceMAC = it.value().toString();

                else if (it.key().compare("Status", Qt::CaseInsensitive) == 0)
                    pRes_A8->Status = it.value().toInt();

                else if (it.key().compare("patientName", Qt::CaseInsensitive) == 0)
                    pRes_A8->patientName = it.value().toString();
                else if (it.key().compare("patientId", Qt::CaseInsensitive) == 0)
                    pRes_A8->patientId = it.value().toString();
                else if (it.key().compare("sex", Qt::CaseInsensitive) == 0)
                    pRes_A8->sex = it.value().toString();
                else if (it.key().compare("age", Qt::CaseInsensitive) == 0)
                    pRes_A8->age = it.value().toString();
                else if (it.key().compare("recordId", Qt::CaseInsensitive) == 0)
                    pRes_A8->recordId = it.value().toString();
                it++;
            }
        }
    }

    if (pRes_A8 != nullptr && pZTServer_api != nullptr && pConfig != nullptr)
    {
        RespondObj_A8 A8Data;
        A8Data.obj.deviceId = pConfig->Get_deviceId();
        A8Data.obj.recordId = pRes_A8->recordId;

        A8Data.obj.patientId = pRes_A8->patientId;
        A8Data.obj.patientName = pRes_A8->patientName;
        A8Data.obj.sex = pRes_A8->sex;
        A8Data.obj.age = pRes_A8->age;

        // 提交设备治疗参数
        pZTServer_api->receiveDevicesData(A8Data.ToJson());

        /// <summary>
        /// 运动状态
        /// 0-空闲
        /// 1-运动中
        /// 2-暂停
        /// 3-急停
        /// </summary>
        if (pRes_A8->Status == 1 || pRes_A8->Status == 2)
        {
            // 同步治疗状态: 1:开始治疗；2：结束治疗;3：拒绝治疗
            QDateTime time;
            QString status = QString::number(pRes_A8->Status);
            pZTServer_api->syncTreatStatus(pConfig->Get_deviceId(), pRes_A8->recordId, status
                                           , time.currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        }
    }
    return pRes_A8;
}
