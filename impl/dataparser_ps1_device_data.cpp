// 2023-06-15, Bruce

#include "dataparser_ps1_device_data.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QStringList>
#include <QDebug>
#include "entity/data_device_data_ps1.h"
#include "entity/respondobj_ps1.h"
#include <QDateTime>

DataParser_PS1_Device_Data::DataParser_PS1_Device_Data()
{

}

// 解析设备发送TCP数据
// 康复设备上传实时信息
IDataBase_Device* DataParser_PS1_Device_Data::ParseData(IDeviceStatus* pDeviceStatus, IConfig* pConfig, IZTServer_api* pZTServer_api, const QString& respond)
{
    Data_Device_Data_PS1* pRes_PS1 = nullptr;

    QJsonParseError jsonerror;
    QJsonDocument doc = QJsonDocument::fromJson(respond.toUtf8(), &jsonerror);
    if (!doc.isNull() && jsonerror.error == QJsonParseError::NoError)
    {
        if (doc.isObject())
        {
            pRes_PS1 = new Data_Device_Data_PS1();
            QJsonObject object = doc.object();
            QStringList list = object.keys();

            QJsonObject::iterator it = object.begin();
            while (it != object.end())
            {
                // 数据包格式
                if (it.key().compare("DataType", Qt::CaseInsensitive) == 0)
                    pRes_PS1->DataType = it.value().toInt();
                else if (it.key().compare("DeviceType", Qt::CaseInsensitive) == 0)
                    pRes_PS1->DeviceType = it.value().toString();
                else if (it.key().compare("DeviceMAC", Qt::CaseInsensitive) == 0)
                    pRes_PS1->DeviceMAC = it.value().toString();

                else if (it.key().compare("Status", Qt::CaseInsensitive) == 0)
                    pRes_PS1->Status = it.value().toInt();

                else if (it.key().compare("patientName", Qt::CaseInsensitive) == 0)
                    pRes_PS1->patientName = it.value().toString();
                else if (it.key().compare("patientId", Qt::CaseInsensitive) == 0)
                    pRes_PS1->patientId = it.value().toString();
                else if (it.key().compare("sex", Qt::CaseInsensitive) == 0)
                    pRes_PS1->sex = it.value().toString();
                else if (it.key().compare("age", Qt::CaseInsensitive) == 0)
                    pRes_PS1->age = it.value().toString();
                else if (it.key().compare("recordId", Qt::CaseInsensitive) == 0)
                    pRes_PS1->recordId = it.value().toString();
                it++;
            }
        }
    }

    if (pRes_PS1 != nullptr && pZTServer_api != nullptr && pConfig != nullptr)
    {
        RespondObj_PS1 PS1Data;
        PS1Data.obj.deviceId = pConfig->Get_deviceId();
        PS1Data.obj.recordId = pRes_PS1->recordId;

        PS1Data.obj.patientId = pRes_PS1->patientId;
        PS1Data.obj.patientName = pRes_PS1->patientName;
        PS1Data.obj.sex = pRes_PS1->sex;
        PS1Data.obj.age = pRes_PS1->age;

        // 提交设备治疗参数
        pZTServer_api->receiveDevicesData(PS1Data.ToJson());

        /// <summary>
        /// 运动状态
        /// 0-空闲
        /// 1-运动中
        /// 2-暂停
        /// 3-急停
        /// </summary>
        if (pRes_PS1->Status == 1 || pRes_PS1->Status == 2)
        {
            // 同步治疗状态: 1:开始治疗；2：结束治疗;3：拒绝治疗
            QDateTime time;
            QString status = QString::number(pRes_PS1->Status);
            pZTServer_api->syncTreatStatus(pConfig->Get_deviceId(), pRes_PS1->recordId, status
                                           , time.currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        }
    }
    return pRes_PS1;
}
