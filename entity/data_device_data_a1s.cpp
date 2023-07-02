// 2023-03-15, Bruce

#include "data_device_data_a1s.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QDebug>
#include "util/jsontools.h"

Data_Device_Data_A1S::Data_Device_Data_A1S()
{

}

QByteArray Data_Device_Data_A1S::ToJson()
{
    QJsonObject obj;
    obj.insert("DataType", DataType);
    obj.insert("DeviceType", DeviceType);
    obj.insert("DeviceMAC", DeviceMAC);

    obj.insert("Status", Status);
    obj.insert("VelocityCur", VelocityCur);
    obj.insert("Duration", Duration);

    obj.insert("AngleFromLeft", AngleFromLeft);
    obj.insert("AngleToLeft", AngleToLeft);
    obj.insert("AngleFromRight", AngleFromRight);
    obj.insert("AngleToRight", AngleToRight);
    obj.insert("VelocityCur", VelocityCur);

    obj.insert("patientName", patientName);
    obj.insert("patientId", patientId);
    obj.insert("sex", sex);
    obj.insert("age", age);
    obj.insert("recordId", recordId);

    return JsonTools::ToArray(obj);
}
