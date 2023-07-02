// 2023-06-13, Bruce

#include "data_device_data_a1.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QDebug>
#include "util/jsontools.h"

Data_Device_Data_A1::Data_Device_Data_A1()
{

}

QByteArray Data_Device_Data_A1::ToJson()
{
    QJsonObject obj;
    obj.insert("DataType", DataType);
    obj.insert("DeviceType", DeviceType);
    obj.insert("DeviceMAC", DeviceMAC);

    obj.insert("Status", Status);
    obj.insert("TreatType", TreatType);
    obj.insert("TrainMode", TrainMode);
    obj.insert("VelocityCur", VelocityCur);
    obj.insert("VelocityReduction", VelocityReduction);
    obj.insert("Duration", Duration);
    obj.insert("RestDuration", RestDuration);

    obj.insert("AngleFromLeft", AngleFromLeft);
    obj.insert("AngleToLeft", AngleToLeft);
    obj.insert("AngleFromRight", AngleFromRight);
    obj.insert("AngleToRight", AngleToRight);
    obj.insert("ScrampSensitivityLeft", ScrampSensitivityLeft);
    obj.insert("ScrampSensitivityRight", ScrampSensitivityRight);

    obj.insert("patientName", patientName);
    obj.insert("patientId", patientId);
    obj.insert("sex", sex);
    obj.insert("age", age);
    obj.insert("recordId", recordId);

    return JsonTools::ToArray(obj);
}
