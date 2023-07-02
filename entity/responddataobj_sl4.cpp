// 2023-03-03, Bruce

#include "responddataobj_sl4.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QDebug>

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

    QJsonDocument doc;
    doc.setObject(obj);
    QByteArray byteArray = doc.toJson(QJsonDocument::Compact);
    QString strJson(byteArray);
    qDebug() << strJson;
    return byteArray;
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
