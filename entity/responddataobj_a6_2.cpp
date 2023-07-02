// 2023-06-13, Bruce

#include "responddataobj_a6_2.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QDebug>

RespondDataObj_A6_2::RespondDataObj_A6_2()
{

}

QByteArray RespondDataObj_A6_2::ToJson()
{
    QJsonObject obj;
    obj.insert("recordId", recordId);
    obj.insert("deviceId", deviceId);

    obj.insert("patientName", patientName);
    obj.insert("patientId", patientId);
    obj.insert("sex", sex);
    obj.insert("age", age);

    QJsonDocument doc;
    doc.setObject(obj);
    QByteArray byteArray = doc.toJson(QJsonDocument::Compact);
    QString strJson(byteArray);
    qDebug() << strJson;
    return byteArray;
}

bool RespondDataObj_A6_2::IsValid()
{
    return true;
}
