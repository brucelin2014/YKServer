// 2023-06-13, Bruce

#include "responddataobj_a1.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QDebug>
#include "util/jsontools.h"

RespondDataObj_A1::RespondDataObj_A1()
{

}

QByteArray RespondDataObj_A1::ToJson()
{
    QJsonObject obj;
    obj.insert("recordId", recordId);
    obj.insert("deviceId", deviceId);

    obj.insert("patientName", patientName);
    obj.insert("patientId", patientId);
    obj.insert("sex", sex);
    obj.insert("age", age);

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

    return JsonTools::ToArray(obj);
}

bool RespondDataObj_A1::IsValid()
{
    if (AngleFromLeft.isEmpty()
            && AngleToLeft.isEmpty()
            && AngleFromRight.isEmpty()
            && AngleToRight.isEmpty()
            && patientId.isEmpty()
            )
        return false;
    return true;
}
