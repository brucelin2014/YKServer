// 2023-06-16, Bruce

#include "dataparser_a3_2.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QStringList>
#include <QDebug>
#include "entity/respondobj_a3_2.h"

DataParser_A3_2::DataParser_A3_2()
{

}

// 解析中天平台HTTP返回数据
IRespondData* DataParser_A3_2::ParseData(const ZTS_API& api, const QString& respond)
{
    RespondObj_A3_2* pRes_A3_2 = nullptr;

    QJsonParseError jsonerror;
    QJsonDocument doc = QJsonDocument::fromJson(respond.toUtf8(), &jsonerror);
    if (!doc.isNull() && jsonerror.error == QJsonParseError::NoError)
    {
        if (doc.isObject())
        {
            pRes_A3_2 = new RespondObj_A3_2();
            QJsonObject object = doc.object();
            QStringList list = object.keys();

            QJsonObject::iterator it = object.begin();
            while (it != object.end())
            {
                // 数据包格式
                if (it.key().compare("code", Qt::CaseInsensitive) == 0)
                    pRes_A3_2->code = it.value().toInt();
                else if (it.key().compare("msg", Qt::CaseInsensitive) == 0)
                    pRes_A3_2->msg = it.value().toString();
                else if (it.key().compare("total", Qt::CaseInsensitive) == 0)
                    pRes_A3_2->total = it.value().toInt();
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

                            // 治疗方案
                            if (it_item.key().compare("recordId", Qt::CaseInsensitive) == 0)
                                pRes_A3_2->obj.recordId = it_item.value().toString();
                            else if (it_item.key().compare("deviceId", Qt::CaseInsensitive) == 0)
                                pRes_A3_2->obj.deviceId = it_item.value().toString();

                            // 用户信息
                            else if (it_item.key().compare("patientName", Qt::CaseInsensitive) == 0)
                                pRes_A3_2->obj.patientName = it_item.value().toString();
                            else if (it_item.key().compare("patientId", Qt::CaseInsensitive) == 0)
                                pRes_A3_2->obj.patientId = it_item.value().toString();
                            else if (it_item.key().compare("sex", Qt::CaseInsensitive) == 0)
                                pRes_A3_2->obj.sex = it_item.value().toString();
                            else if (it_item.key().compare("age", Qt::CaseInsensitive) == 0)
                            {
                                pRes_A3_2->obj.age = it_item.value().toString();
                                pRes_A3_2->obj.age.replace(pRes_A3_2->obj.age.indexOf("岁"), 1, "");
                            }

                            it_item++;
                        }
                    }
                }
                it++;
            }
        }
    }
    return pRes_A3_2;
}
