// 2023-06-16, Bruce

#include "dataparser_a6_2.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QStringList>
#include <QDebug>
#include "entity/respondobj_a6_2.h"

DataParser_A6_2::DataParser_A6_2()
{

}

// 解析中天平台HTTP返回数据
IRespondData* DataParser_A6_2::ParseData(const ZTS_API& api, const QString& obj)
{
    RespondObj_A6_2* pRes_A6_2 = nullptr;

    QJsonParseError jsonerror;
    QJsonDocument doc = QJsonDocument::fromJson(obj.toUtf8(), &jsonerror);
    if (!doc.isNull() && jsonerror.error == QJsonParseError::NoError)
    {
        if (doc.isObject())
        {
            pRes_A6_2 = new RespondObj_A6_2();
            QJsonObject object_item = doc.object();
            QJsonObject::iterator it_item = object_item.begin();
            while (it_item != object_item.end())
            {
                QString obj_key = it_item.key();
                QString obj_val = it_item.value().isDouble() ? QString::number(it_item.value().toInt()) : it_item.value().toString();

                // 设备训练参数
//                if (obj_key.compare("AngleFromLeft", Qt::CaseInsensitive) == 0)
//                    pRes_A6_2->obj.AngleFromLeft = obj_val;
//                else if (obj_key.compare("AngleToLeft", Qt::CaseInsensitive) == 0)
//                    pRes_A6_2->obj.AngleToLeft = obj_val;
//                else if (obj_key.compare("AngleFromRight", Qt::CaseInsensitive) == 0)
//                    pRes_A6_2->obj.AngleFromRight = obj_val;
//                else if (obj_key.compare("AngleToRight", Qt::CaseInsensitive) == 0)
//                    pRes_A6_2->obj.AngleToRight = obj_val;
//                else if (obj_key.compare("Duration", Qt::CaseInsensitive) == 0)
//                    pRes_A6_2->obj.Duration = obj_val;
//                else if (obj_key.compare("VelocityCur", Qt::CaseInsensitive) == 0)
//                    pRes_A6_2->obj.VelocityCur = obj_val;

                // 治疗方案
                if (obj_key.compare("recordId", Qt::CaseInsensitive) == 0)
                    pRes_A6_2->obj.recordId = obj_val;
                else if (obj_key.compare("deviceId", Qt::CaseInsensitive) == 0)
                    pRes_A6_2->obj.deviceId = obj_val;

                // 用户信息
                else if (obj_key.compare("patientName", Qt::CaseInsensitive) == 0)
                    pRes_A6_2->obj.patientName = obj_val;
                else if (obj_key.compare("patientId", Qt::CaseInsensitive) == 0)
                    pRes_A6_2->obj.patientId = obj_val;
                else if (obj_key.compare("sex", Qt::CaseInsensitive) == 0)
                    pRes_A6_2->obj.sex = obj_val;
                else if (obj_key.compare("age", Qt::CaseInsensitive) == 0)
                {
                    pRes_A6_2->obj.age = obj_val;
                    pRes_A6_2->obj.age.replace(pRes_A6_2->obj.age.indexOf("岁"), 1, "");
                }

                // 华唯新协议
                if (obj_key.compare("dev_param", Qt::CaseInsensitive) == 0)
                {
                    QJsonObject object_item_dev = it_item.value().toObject();
                    QStringList list_item_dev = object_item_dev.keys();

                    QJsonObject::iterator it_item_dev = object_item_dev.begin();
                    while (it_item_dev != object_item_dev.end())
                    {
                        QString dev_key = it_item_dev.key();
                        QString dev_val = it_item_dev.value().isDouble() ? QString::number(it_item_dev.value().toInt()) : it_item_dev.value().toString();

                        // 设备训练参数
//                        if (dev_key.compare("TreatType", Qt::CaseInsensitive) == 0)
//                            pRes_A6_2->obj.TreatType = dev_val;
//                        else if (dev_key.compare("TrainMode", Qt::CaseInsensitive) == 0)
//                            pRes_A6_2->obj.TrainMode = dev_val;

//                        else if (dev_key.compare("VelocityCur", Qt::CaseInsensitive) == 0)
//                            pRes_A6_2->obj.VelocityCur = dev_val;
//                        else if (dev_key.compare("VelocityReduction", Qt::CaseInsensitive) == 0)
//                            pRes_A6_2->obj.VelocityReduction = dev_val;

//                        else if (dev_key.compare("Duration", Qt::CaseInsensitive) == 0)
//                            pRes_A6_2->obj.Duration = dev_val;
//                        else if (dev_key.compare("RestDuration", Qt::CaseInsensitive) == 0)
//                            pRes_A6_2->obj.RestDuration = dev_val;

//                        else if (dev_key.compare("AngleFromLeft", Qt::CaseInsensitive) == 0)
//                            pRes_A6_2->obj.AngleFromLeft = dev_val;
//                        else if (dev_key.compare("AngleToLeft", Qt::CaseInsensitive) == 0)
//                            pRes_A6_2->obj.AngleToLeft = dev_val;
//                        else if (dev_key.compare("AngleFromRight", Qt::CaseInsensitive) == 0)
//                            pRes_A6_2->obj.AngleFromRight = dev_val;
//                        else if (dev_key.compare("AngleToRight", Qt::CaseInsensitive) == 0)
//                            pRes_A6_2->obj.AngleToRight = dev_val;

//                        else if (dev_key.compare("ScrampSensitivityLeft", Qt::CaseInsensitive) == 0)
//                            pRes_A6_2->obj.ScrampSensitivityLeft = dev_val;
//                        else if (dev_key.compare("ScrampSensitivityRight", Qt::CaseInsensitive) == 0)
//                            pRes_A6_2->obj.ScrampSensitivityRight = dev_val;

                        it_item_dev++;
                    }
                }

                it_item++;
            }
        }
    }
    return pRes_A6_2;
}
