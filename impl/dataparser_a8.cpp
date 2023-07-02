// 2023-06-16, Bruce

#include "dataparser_a8.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QStringList>
#include <QDebug>
#include "entity/respondobj_a8.h"

DataParser_A8::DataParser_A8()
{

}

// 解析中天平台HTTP返回数据
IRespondData* DataParser_A8::ParseData(const ZTS_API& api, const QString& respond)
{
    RespondObj_A8* pRes_A8 = nullptr;

    QJsonParseError jsonerror;
    QJsonDocument doc = QJsonDocument::fromJson(respond.toUtf8(), &jsonerror);
    if (!doc.isNull() && jsonerror.error == QJsonParseError::NoError)
    {
        if (doc.isObject())
        {
            pRes_A8 = new RespondObj_A8();
            QJsonObject object = doc.object();
            QStringList list = object.keys();

            QJsonObject::iterator it = object.begin();
            while (it != object.end())
            {
                // 数据包格式
                if (it.key().compare("code", Qt::CaseInsensitive) == 0)
                    pRes_A8->code = it.value().toInt();
                else if (it.key().compare("msg", Qt::CaseInsensitive) == 0)
                    pRes_A8->msg = it.value().toString();
                else if (it.key().compare("total", Qt::CaseInsensitive) == 0)
                    pRes_A8->total = it.value().toInt();
                else if (it.key().compare("obj", Qt::CaseInsensitive) == 0)
                {
                    // 解析JSON数值
                    if (it.value().type() != QJsonValue::Object)
                    {
                        pRes_A8->status = it.value().toString();
                    }
                    else // 解析JSON对象
                    {
                        QJsonObject object_item = it.value().toObject();
                        QStringList list_item = object_item.keys();

                        QJsonObject::iterator it_item = object_item.begin();
                        while (it_item != object_item.end())
                        {
                            // 训练参数

                            // 治疗方案
                            if (it_item.key().compare("recordId", Qt::CaseInsensitive) == 0)
                                pRes_A8->obj.recordId = it_item.value().toString();
                            else if (it_item.key().compare("deviceId", Qt::CaseInsensitive) == 0)
                                pRes_A8->obj.deviceId = it_item.value().toString();

                            // 用户信息
                            else if (it_item.key().compare("patientName", Qt::CaseInsensitive) == 0)
                                pRes_A8->obj.patientName = it_item.value().toString();
                            else if (it_item.key().compare("patientId", Qt::CaseInsensitive) == 0)
                                pRes_A8->obj.patientId = it_item.value().toString();
                            else if (it_item.key().compare("sex", Qt::CaseInsensitive) == 0)
                                pRes_A8->obj.sex = it_item.value().toString();
                            else if (it_item.key().compare("age", Qt::CaseInsensitive) == 0)
                            {
                                pRes_A8->obj.age = it_item.value().toString();
                                pRes_A8->obj.age.replace(pRes_A8->obj.age.indexOf("岁"), 1, "");
                            }

                            it_item++;
                        }
                    }
                }
                it++;
            }
        }
    }
    return pRes_A8;
}