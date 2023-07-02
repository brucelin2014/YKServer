// 2023-07-02, Bruce

#include "dataparser_treat_plan.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QStringList>
#include <QDebug>
#include "entity/respondobj_treat_plan.h"

DataParser_Treat_Plan::DataParser_Treat_Plan()
{

}

// 解析中天平台HTTP返回数据
IRespondData* DataParser_Treat_Plan::ParseData(const ZTS_API& api, const QString& obj)
{
    RespondObj_Treat_Plan* pRes = nullptr;

    QJsonParseError jsonerror;
    QJsonDocument doc = QJsonDocument::fromJson(obj.toUtf8(), &jsonerror);
    if (!doc.isNull() && jsonerror.error == QJsonParseError::NoError)
    {
        if (doc.isObject())
        {
            pRes = new RespondObj_Treat_Plan();
            QJsonObject object_item = doc.object();
            QJsonObject::iterator it_item = object_item.begin();
            while (it_item != object_item.end())
            {
                QString obj_key = it_item.key();
                QString obj_val = it_item.value().isDouble() ? QString::number(it_item.value().toInt()) : it_item.value().toString();

                // 治疗方案
                if (obj_key.compare("recordId", Qt::CaseInsensitive) == 0)
                    pRes->obj.recordId = obj_val;
                else if (obj_key.compare("deviceId", Qt::CaseInsensitive) == 0)
                    pRes->obj.deviceId = obj_val;

                // 用户信息
                else if (obj_key.compare("patientName", Qt::CaseInsensitive) == 0)
                    pRes->obj.patientName = obj_val;
                else if (obj_key.compare("patientId", Qt::CaseInsensitive) == 0)
                    pRes->obj.patientId = obj_val;
                else if (obj_key.compare("sex", Qt::CaseInsensitive) == 0)
                    pRes->obj.sex = obj_val;
                else if (obj_key.compare("age", Qt::CaseInsensitive) == 0)
                {
                    pRes->obj.age = obj_val;
                    pRes->obj.age.replace(pRes->obj.age.indexOf("岁"), 1, "");
                }

                it_item++;
            }
        }
    }
    return pRes;
}
