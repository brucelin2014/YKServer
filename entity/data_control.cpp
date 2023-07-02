// 2023-06-13, Bruce

#include "data_control.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QDebug>

Data_Control::Data_Control()
{

}

QByteArray Data_Control::ToJson()
{
    QJsonObject obj;
    obj.insert("DataType", DataType);
    obj.insert("DeviceType", DeviceType);
    obj.insert("DeviceMAC", DeviceMAC);

    obj.insert("Status", Status);

    QJsonDocument doc;
    doc.setObject(obj);
    QByteArray byteArray = doc.toJson(QJsonDocument::Compact);
    //QString strJson(byteArray);
    //qDebug() << strJson;
    return byteArray;
}
