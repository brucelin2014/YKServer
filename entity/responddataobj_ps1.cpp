// 2023-06-13, Bruce

#include "responddataobj_ps1.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QDebug>
#include "util/jsontools.h"

RespondDataObj_PS1::RespondDataObj_PS1()
{

}

QByteArray RespondDataObj_PS1::ToJson()
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

bool RespondDataObj_PS1::IsValid()
{
    return true;
}
