// 2023-03-15, Bruce

#include "dataparser_device_report.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QStringList>
#include <QDebug>
#include "entity/data_device_report.h"
#include <QDateTime>

DataParser_Device_Report::DataParser_Device_Report()
{

}

// 解析设备发送TCP数据
IDataBase_Device* DataParser_Device_Report::ParseData(IDeviceStatus* pDeviceStatus, IConfig* pConfig, IZTServer_api* pZTServer_api, const QString& respond)
{
    Data_Device_Report* pRes_a1s = nullptr;

    QJsonParseError jsonerror;
    QJsonDocument doc = QJsonDocument::fromJson(respond.toUtf8(), &jsonerror);
    if (!doc.isNull() && jsonerror.error == QJsonParseError::NoError)
    {
        if (doc.isObject())
        {
            pRes_a1s = new Data_Device_Report();
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

                else if (it.key().compare("age", Qt::CaseInsensitive) == 0)
                    pRes_a1s->age = it.value().toString();
                else if (it.key().compare("patientId", Qt::CaseInsensitive) == 0)
                    pRes_a1s->patientId = it.value().toString();
                else if (it.key().compare("sex", Qt::CaseInsensitive) == 0)
                    pRes_a1s->sex = it.value().toString();
                else if (it.key().compare("patientName", Qt::CaseInsensitive) == 0)
                    pRes_a1s->patientName  = it.value().toString();
                else if (it.key().compare("recordId", Qt::CaseInsensitive) == 0)
                    pRes_a1s->recordId = it.value().toString();
                else if (it.key().compare("PdfFileName", Qt::CaseInsensitive) == 0)
                    pRes_a1s->PdfFileName  = it.value().toString();
                it++;
            }
        }
    }

    if (pRes_a1s != nullptr && pConfig != nullptr)
    {
        // 同步治疗状态: 1:开始治疗；2：结束治疗;3：拒绝治疗
        QDateTime time;
        QString status = QString::number(2);
        pZTServer_api->syncTreatStatus(pConfig->Get_deviceId(), pRes_a1s->recordId, status
                                       , time.currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

        // 提交治疗或评定报告
        QString filePath = pConfig->Get_report_folder() + "\\" + pRes_a1s->PdfFileName;
        pZTServer_api->submitReport(filePath, pConfig->Get_deviceId(), pRes_a1s->patientId, pRes_a1s->recordId);
    }
    return pRes_a1s;
}
