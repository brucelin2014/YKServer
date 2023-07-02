// 2023-03-03, Bruce

#include "responddataobj_sl4.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QDebug>
#include "util/jsontools.h"

RespondDataObj_SL4::RespondDataObj_SL4()
{

}

QByteArray RespondDataObj_SL4::ToJson()
{
    QJsonObject obj;
    obj.insert("recordId", recordId);
    obj.insert("deviceId", deviceId);

    obj.insert("patientName", patientName);
    obj.insert("patientId", patientId);
    obj.insert("sex", sex);
    obj.insert("age", age);

    obj.insert("Mode", Mode);
    obj.insert("Content", Content);
    obj.insert("Body", Body);

    return JsonTools::ToArray(obj);
}

bool RespondDataObj_SL4::IsValid()
{
    if (Mode.isEmpty()
            && Content.isEmpty()
            && Body.isEmpty()
            )
        return false;

    if (Mode.isEmpty())
        Mode = "1";

    if (Content.isEmpty())
        Content = "0";

    if (Body.isEmpty())
        Body = "0";
    return true;
}
