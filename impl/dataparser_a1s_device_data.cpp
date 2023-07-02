// 2023-03-15, Bruce

#include "dataparser_a1s_device_data.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QStringList>
#include <QDebug>
#include "entity/data_device_data_a1s.h"
#include "entity/respondobj_a1s.h"
#include <QDateTime>

DataParser_A1S_Device_Data::DataParser_A1S_Device_Data()
{

}

// 解析设备发送TCP数据
// 康复设备上传实时信息
IDataBase_Device* DataParser_A1S_Device_Data::ParseData(IDeviceStatus* pDeviceStatus, IConfig* pConfig, IZTServer_api* pZTServer_api, const QString& respond)
{
    Data_Device_Data_A1S* pRes_a1s = nullptr;

    QJsonParseError jsonerror;
    QJsonDocument doc = QJsonDocument::fromJson(respond.toUtf8(), &jsonerror);
    if (!doc.isNull() && jsonerror.error == QJsonParseError::NoError)
    {
        if (doc.isObject())
        {
            pRes_a1s = new Data_Device_Data_A1S();
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

                else if (it.key().compare("Status", Qt::CaseInsensitive) == 0)
                    pRes_a1s->Status = it.value().toInt();
                else if (it.key().compare("VelocityCur", Qt::CaseInsensitive) == 0)
                    pRes_a1s->VelocityCur = it.value().toInt();
                else if (it.key().compare("Duration", Qt::CaseInsensitive) == 0)
                    pRes_a1s->Duration = it.value().toInt();
                else if (it.key().compare("AngleFromLeft", Qt::CaseInsensitive) == 0)
                    pRes_a1s->AngleFromLeft  = it.value().toInt();
                else if (it.key().compare("AngleToLeft", Qt::CaseInsensitive) == 0)
                    pRes_a1s->AngleToLeft  = it.value().toInt();
                else if (it.key().compare("AngleFromRight", Qt::CaseInsensitive) == 0)
                    pRes_a1s->AngleFromRight  = it.value().toInt();
                else if (it.key().compare("AngleToRight", Qt::CaseInsensitive) == 0)
                    pRes_a1s->AngleToRight  = it.value().toInt();

                else if (it.key().compare("patientName", Qt::CaseInsensitive) == 0)
                    pRes_a1s->patientName = it.value().toString();
                else if (it.key().compare("patientId", Qt::CaseInsensitive) == 0)
                    pRes_a1s->patientId = it.value().toString();
                else if (it.key().compare("sex", Qt::CaseInsensitive) == 0)
                    pRes_a1s->sex = it.value().toString();
                else if (it.key().compare("age", Qt::CaseInsensitive) == 0)
                    pRes_a1s->age = it.value().toString();
                else if (it.key().compare("recordId", Qt::CaseInsensitive) == 0)
                    pRes_a1s->recordId = it.value().toString();
                it++;
            }
        }
    }

    if (pRes_a1s != nullptr && pZTServer_api != nullptr && pConfig != nullptr)
    {
        RespondObj_A1S a1sData;
        a1sData.obj.deviceId = pConfig->Get_deviceId();
        a1sData.obj.recordId = pRes_a1s->recordId;

        a1sData.obj.patientId = pRes_a1s->patientId;
        a1sData.obj.patientName = pRes_a1s->patientName;
        a1sData.obj.sex = pRes_a1s->sex;
        a1sData.obj.age = pRes_a1s->age;

        a1sData.obj.VelocityCur = QString::number(pRes_a1s->VelocityCur);
        a1sData.obj.Duration = QString::number(pRes_a1s->Duration);
        a1sData.obj.AngleFromLeft = QString::number(pRes_a1s->AngleFromLeft);
        a1sData.obj.AngleToLeft = QString::number(pRes_a1s->AngleToLeft);
        a1sData.obj.AngleFromRight = QString::number(pRes_a1s->AngleFromRight);
        a1sData.obj.AngleToRight = QString::number(pRes_a1s->AngleToRight);

        // 提交设备治疗参数
        pZTServer_api->receiveDevicesData(a1sData.ToJson());

        /// <summary>
        /// 运动状态
        /// 0-空闲
        /// 1-运动中
        /// 2-暂停
        /// 3-急停
        /// </summary>
        if (pRes_a1s->Status == 1 || pRes_a1s->Status == 2)
        {
            // 同步治疗状态: 1:开始治疗；2：结束治疗;3：拒绝治疗
            QDateTime time;
            QString status = QString::number(pRes_a1s->Status);
            pZTServer_api->syncTreatStatus(pConfig->Get_deviceId(), pRes_a1s->recordId, status
                                           , time.currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        }
    }
    return pRes_a1s;
}
