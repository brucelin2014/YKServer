// 2023-06-13, Bruce

#include "data_control.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QDebug>
#include "util/jsontools.h"

Data_Control::Data_Control()
    : Status("0")
{

}

QByteArray Data_Control::ToJson()
{
    QJsonObject obj;
    obj.insert("DataType", DataType);
    obj.insert("DeviceType", DeviceType);
    obj.insert("DeviceMAC", DeviceMAC);

    obj.insert("Status", Status);

    return JsonTools::ToArray(obj);
}
