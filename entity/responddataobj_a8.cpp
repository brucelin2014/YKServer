// 2023-06-13, Bruce

#include "responddataobj_a8.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QDebug>
#include "util/jsontools.h"

RespondDataObj_A8::RespondDataObj_A8()
{

}

QByteArray RespondDataObj_A8::ToJson()
{
    QJsonObject obj;
    obj.insert("recordId", recordId);
    obj.insert("deviceId", deviceId);

    obj.insert("patientName", patientName);
    obj.insert("patientId", patientId);
    obj.insert("sex", sex);
    obj.insert("age", age);

    return JsonTools::ToArray(obj);
}

bool RespondDataObj_A8::IsValid()
{
    return true;
}
