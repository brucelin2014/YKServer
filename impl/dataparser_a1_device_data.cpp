// 2023-06-15, Bruce

#include "dataparser_a1_device_data.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QStringList>
#include <QDebug>
#include "entity/data_device_data_a1.h"
#include "entity/respondobj_a1.h"
#include <QDateTime>

DataParser_A1_Device_Data::DataParser_A1_Device_Data()
{

}

// 解析设备发送TCP数据
// 康复设备上传实时信息
IDataBase_Device* DataParser_A1_Device_Data::ParseData(IDeviceStatus* pDeviceStatus, IConfig* pConfig, IZTServer_api* pZTServer_api, const QString& respond)
{
    Data_Device_Data_A1* pRes_A1 = nullptr;

    QJsonParseError jsonerror;
    QJsonDocument doc = QJsonDocument::fromJson(respond.toUtf8(), &jsonerror);
    if (!doc.isNull() && jsonerror.error == QJsonParseError::NoError)
    {
        if (doc.isObject())
        {
            pRes_A1 = new Data_Device_Data_A1();
            QJsonObject object = doc.object();
            QStringList list = object.keys();

            QJsonObject::iterator it = object.begin();
            while (it != object.end())
            {
                // 数据包格式
                if (it.key().compare("DataType", Qt::CaseInsensitive) == 0)
                    pRes_A1->DataType = it.value().toInt();
                else if (it.key().compare("DeviceType", Qt::CaseInsensitive) == 0)
                    pRes_A1->DeviceType = it.value().toString();
                else if (it.key().compare("DeviceMAC", Qt::CaseInsensitive) == 0)
                    pRes_A1->DeviceMAC = it.value().toString();

                else if (it.key().compare("Status", Qt::CaseInsensitive) == 0)
                    pRes_A1->Status = it.value().toInt();

                else if (it.key().compare("VelocityCur", Qt::CaseInsensitive) == 0)
                    pRes_A1->VelocityCur = it.value().toInt();
                else if (it.key().compare("Duration", Qt::CaseInsensitive) == 0)
                    pRes_A1->Duration = it.value().toInt();
                else if (it.key().compare("AngleFromLeft", Qt::CaseInsensitive) == 0)
                    pRes_A1->AngleFromLeft  = it.value().toInt();
                else if (it.key().compare("AngleToLeft", Qt::CaseInsensitive) == 0)
                    pRes_A1->AngleToLeft  = it.value().toInt();
                else if (it.key().compare("AngleFromRight", Qt::CaseInsensitive) == 0)
                    pRes_A1->AngleFromRight  = it.value().toInt();
                else if (it.key().compare("AngleToRight", Qt::CaseInsensitive) == 0)
                    pRes_A1->AngleToRight  = it.value().toInt();

                else if (it.key().compare("patientName", Qt::CaseInsensitive) == 0)
                    pRes_A1->patientName = it.value().toString();
                else if (it.key().compare("patientId", Qt::CaseInsensitive) == 0)
                    pRes_A1->patientId = it.value().toString();
                else if (it.key().compare("sex", Qt::CaseInsensitive) == 0)
                    pRes_A1->sex = it.value().toString();
                else if (it.key().compare("age", Qt::CaseInsensitive) == 0)
                    pRes_A1->age = it.value().toString();
                else if (it.key().compare("recordId", Qt::CaseInsensitive) == 0)
                    pRes_A1->recordId = it.value().toString();
                it++;
            }
        }
    }

    if (pRes_A1 != nullptr && pZTServer_api != nullptr && pConfig != nullptr)
    {
        RespondObj_A1 A1Data;
        A1Data.obj.deviceId = pConfig->Get_deviceId();
        A1Data.obj.recordId = pRes_A1->recordId;

        A1Data.obj.patientId = pRes_A1->patientId;
        A1Data.obj.patientName = pRes_A1->patientName;
        A1Data.obj.sex = pRes_A1->sex;
        A1Data.obj.age = pRes_A1->age;

        A1Data.obj.VelocityCur = QString::number(pRes_A1->VelocityCur);
        A1Data.obj.Duration = QString::number(pRes_A1->Duration);
        A1Data.obj.AngleFromLeft = QString::number(pRes_A1->AngleFromLeft);
        A1Data.obj.AngleToLeft = QString::number(pRes_A1->AngleToLeft);
        A1Data.obj.AngleFromRight = QString::number(pRes_A1->AngleFromRight);
        A1Data.obj.AngleToRight = QString::number(pRes_A1->AngleToRight);

        // 提交设备治疗参数
        pZTServer_api->receiveDevicesData(A1Data.ToJson());

        /// <summary>
        /// 运动状态
        /// 0-空闲
        /// 1-运动中
        /// 2-暂停
        /// 3-急停
        /// </summary>
        if (pRes_A1->Status == 1 || pRes_A1->Status == 2)
        {
            // 同步治疗状态: 1:开始治疗；2：结束治疗;3：拒绝治疗
            QDateTime time;
            QString status = QString::number(pRes_A1->Status);
            pZTServer_api->syncTreatStatus(pConfig->Get_deviceId(), pRes_A1->recordId, status
                                           , time.currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        }
    }
    return pRes_A1;
}
