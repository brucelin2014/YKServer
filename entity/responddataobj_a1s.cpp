// 2023-03-03, Bruce

#include "responddataobj_a1s.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QDebug>
#include "util/jsontools.h"

RespondDataObj_A1S::RespondDataObj_A1S()
{

}

QByteArray RespondDataObj_A1S::ToJson()
{
    QJsonObject obj;
    obj.insert("recordId", recordId);
    obj.insert("deviceId", deviceId);

    obj.insert("patientName", patientName);
    obj.insert("patientId", patientId);
    obj.insert("sex", sex);
    obj.insert("age", age);

    obj.insert("AngleFromLeft", AngleFromLeft);
    obj.insert("AngleToLeft", AngleToLeft);
    obj.insert("AngleFromRight", AngleFromRight);
    obj.insert("AngleToRight", AngleToRight);
    obj.insert("VelocityCur", VelocityCur);
    obj.insert("Duration", Duration);

    return JsonTools::ToArray(obj);
}

bool RespondDataObj_A1S::IsValid()
{
    if (AngleFromLeft.isEmpty()
            || AngleToLeft.isEmpty()
            || AngleFromRight.isEmpty()
            || AngleToRight.isEmpty()
            || patientId.isEmpty()
            )
        return false;
    return true;
}
