// 2023-06-16, Bruce

#include "data_device_data_a3_2.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QDebug>

Data_Device_Data_A3_2::Data_Device_Data_A3_2()
{

}

QByteArray Data_Device_Data_A3_2::ToJson()
{
    QJsonObject obj;
    obj.insert("DataType", DataType);
    obj.insert("DeviceType", DeviceType);
    obj.insert("DeviceMAC", DeviceMAC);

    obj.insert("Status", Status);

    obj.insert("patientName", patientName);
    obj.insert("patientId", patientId);
    obj.insert("sex", sex);
    obj.insert("age", age);
    obj.insert("recordId", recordId);

    QJsonDocument doc;
    doc.setObject(obj);
    QByteArray byteArray = doc.toJson(QJsonDocument::Compact);
    //QString strJson(byteArray);
    //qDebug() << strJson;
    return byteArray;
}
