// 2023-07-02, Bruce

#include "respondobj_treat_plan.h"
#include "util/jsontools.h"
#include <QJsonObject>

RespondObj_Treat_Plan::RespondObj_Treat_Plan()
{

}

QByteArray RespondObj_Treat_Plan::ToJson()
{
    QJsonObject json_obj;
    json_obj.insert("recordId", obj.recordId);
    json_obj.insert("deviceId", obj.deviceId);

    json_obj.insert("patientName", obj.patientName);
    json_obj.insert("patientId", obj.patientId);
    json_obj.insert("sex", obj.sex);
    json_obj.insert("age", obj.age);

    return JsonTools::ToArray(json_obj);
}
