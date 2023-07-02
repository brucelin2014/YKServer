// 2023-07-02, Bruce

#include "dataparser.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QStringList>
#include <QDebug>
#include "util/jsontools.h"

DataParser::DataParser()
{

}

// 解析中天平台HTTP返回数据
RespondObj* DataParser::ParseData(const QString& respond)
{
    RespondObj* pRes = nullptr;

    QJsonParseError jsonerror;
    QJsonDocument doc = QJsonDocument::fromJson(respond.toUtf8(), &jsonerror);
    if (!doc.isNull() && jsonerror.error == QJsonParseError::NoError)
    {
        if (doc.isObject())
        {
            pRes = new RespondObj();
            QJsonObject object = doc.object();
            QStringList list = object.keys();

            QJsonObject::iterator it = object.begin();
            while (it != object.end())
            {
                // 数据包格式
                if (it.key().compare("code", Qt::CaseInsensitive) == 0)
                    pRes->code = it.value().toInt();
                else if (it.key().compare("msg", Qt::CaseInsensitive) == 0)
                    pRes->msg = it.value().toString();
                else if (it.key().compare("total", Qt::CaseInsensitive) == 0)
                    pRes->total = it.value().toInt();
                else if (it.key().compare("obj", Qt::CaseInsensitive) == 0)
                {
                    // 解析JSON数值
                    QJsonValue type = it.value().type();
                    if (type == QJsonValue::Null)
                    {
                        pRes->status = "0";
                    }
                    else if (type == QJsonValue::Object)
                    {
                        pRes->obj = JsonTools::ToString(it.value().toObject());
                    }
                    else if (type == QJsonValue::String || type == QJsonValue::Double)
                    {
                        QString val = it.value().isDouble() ? QString::number(it.value().toInt()) : it.value().toString();
                        pRes->status = val;
                        if (pRes->status.isEmpty())
                            pRes->status = "0";
                    }
                }
                it++;
            }
        }
    }
    return pRes;
}

// 更新医嘱Obj
bool DataParser::UpdateObj(QString& obj)
{
    QJsonParseError jsonerror;
    QJsonDocument doc = QJsonDocument::fromJson(obj.toUtf8(), &jsonerror);
    if (!doc.isNull() && jsonerror.error == QJsonParseError::NoError)
    {
        if (doc.isObject())
        {
            QJsonObject json_obj = doc.object();

            json_obj.insert("DataType", 3);
            json_obj.insert("DeviceType", "");
            json_obj.insert("DeviceMAC", "");

            obj = JsonTools::ToString(json_obj);
            return true;
        }
    }
    return false;
}
