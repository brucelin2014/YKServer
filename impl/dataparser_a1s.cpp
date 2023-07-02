// 2023-03-03, Bruce

#include "dataparser_a1s.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QStringList>
#include <QDebug>
#include "entity/respondobj_a1s.h"

DataParser_A1S::DataParser_A1S()
{

}

// 解析中天平台HTTP返回数据
IRespondData* DataParser_A1S::ParseData(const ZTS_API& api, const QString& respond)
{
    RespondObj_A1S* pRes_a1s = nullptr;

    QJsonParseError jsonerror;
    QJsonDocument doc = QJsonDocument::fromJson(respond.toUtf8(), &jsonerror);
    if (!doc.isNull() && jsonerror.error == QJsonParseError::NoError)
    {
        if (doc.isObject())
        {
            pRes_a1s = new RespondObj_A1S();
            QJsonObject object = doc.object();
            QStringList list = object.keys();

            QJsonObject::iterator it = object.begin();
            while (it != object.end())
            {
                // 数据包格式
                if (it.key().compare("code", Qt::CaseInsensitive) == 0)
                    pRes_a1s->code = it.value().toInt();
                else if (it.key().compare("msg", Qt::CaseInsensitive) == 0)
                    pRes_a1s->msg = it.value().toString();
                else if (it.key().compare("total", Qt::CaseInsensitive) == 0)
                    pRes_a1s->total = it.value().toInt();
                else if (it.key().compare("obj", Qt::CaseInsensitive) == 0)
                {
                    if (it.value().type() == QJsonValue::Object)
                    {
                        QJsonObject object_item = it.value().toObject();
                        QStringList list_item = object_item.keys();

                        QJsonObject::iterator it_item = object_item.begin();
                        while (it_item != object_item.end())
                        {
                            // 训练参数
                            if (it_item.key().compare("AngleFromLeft", Qt::CaseInsensitive) == 0)
                                pRes_a1s->obj.AngleFromLeft = it_item.value().toString();
                            else if (it_item.key().compare("AngleToLeft", Qt::CaseInsensitive) == 0)
                                pRes_a1s->obj.AngleToLeft = it_item.value().toString();
                            else if (it_item.key().compare("AngleFromRight", Qt::CaseInsensitive) == 0)
                                pRes_a1s->obj.AngleFromRight = it_item.value().toString();
                            else if (it_item.key().compare("AngleToRight", Qt::CaseInsensitive) == 0)
                                pRes_a1s->obj.AngleToRight = it_item.value().toString();
                            else if (it_item.key().compare("Duration", Qt::CaseInsensitive) == 0)
                                pRes_a1s->obj.Duration = it_item.value().toString();
                            else if (it_item.key().compare("VelocityCur", Qt::CaseInsensitive) == 0)
                                pRes_a1s->obj.VelocityCur = it_item.value().toString();

                            // 治疗方案
                            else if (it_item.key().compare("recordId", Qt::CaseInsensitive) == 0)
                                pRes_a1s->obj.recordId = it_item.value().toString();
                            else if (it_item.key().compare("deviceId", Qt::CaseInsensitive) == 0)
                                pRes_a1s->obj.deviceId = it_item.value().toString();

                            // 用户信息
                            else if (it_item.key().compare("patientName", Qt::CaseInsensitive) == 0)
                                pRes_a1s->obj.patientName = it_item.value().toString();
                            else if (it_item.key().compare("patientId", Qt::CaseInsensitive) == 0)
                                pRes_a1s->obj.patientId = it_item.value().toString();
                            else if (it_item.key().compare("sex", Qt::CaseInsensitive) == 0)
                                pRes_a1s->obj.sex = it_item.value().toString();
                            else if (it_item.key().compare("age", Qt::CaseInsensitive) == 0)
                            {
                                pRes_a1s->obj.age = it_item.value().toString();
                                pRes_a1s->obj.age.replace(pRes_a1s->obj.age.indexOf("岁"), 1, "");
                            }

                            it_item++;
                        }
                    }
                }
                it++;
            }
        }
    }
    return pRes_a1s;
}
