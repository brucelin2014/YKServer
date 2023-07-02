// 2023-06-16, Bruce

#include "dataparser_a1.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QStringList>
#include <QDebug>
#include "entity/respondobj_a1.h"

DataParser_A1::DataParser_A1()
{

}

// 解析中天平台HTTP返回数据
IRespondData* DataParser_A1::ParseData(const ZTS_API& api, const QString& respond)
{
    RespondObj_A1* pRes_A1 = nullptr;

    QJsonParseError jsonerror;
    QJsonDocument doc = QJsonDocument::fromJson(respond.toUtf8(), &jsonerror);
    if (!doc.isNull() && jsonerror.error == QJsonParseError::NoError)
    {
        if (doc.isObject())
        {
            pRes_A1 = new RespondObj_A1();
            QJsonObject object = doc.object();
            QStringList list = object.keys();

            QJsonObject::iterator it = object.begin();
            while (it != object.end())
            {
                // 数据包格式
                if (it.key().compare("code", Qt::CaseInsensitive) == 0)
                    pRes_A1->code = it.value().toInt();
                else if (it.key().compare("msg", Qt::CaseInsensitive) == 0)
                    pRes_A1->msg = it.value().toString();
                else if (it.key().compare("total", Qt::CaseInsensitive) == 0)
                    pRes_A1->total = it.value().toInt();
                else if (it.key().compare("obj", Qt::CaseInsensitive) == 0)
                {
                    // 解析JSON数值
                    if (it.value().type() != QJsonValue::Object)
                    {
                        pRes_A1->status = it.value().toString();
                        if (pRes_A1->status.isEmpty())
                            pRes_A1->status = "0";
                    }
                    else // 解析JSON对象
                    {
                        QJsonObject object_item = it.value().toObject();
                        QStringList list_item = object_item.keys();

                        QJsonObject::iterator it_item = object_item.begin();
                        while (it_item != object_item.end())
                        {
                            // 设备训练参数
                            if (it_item.key().compare("AngleFromLeft", Qt::CaseInsensitive) == 0)
                                pRes_A1->obj.AngleFromLeft = it_item.value().toString();
                            else if (it_item.key().compare("AngleToLeft", Qt::CaseInsensitive) == 0)
                                pRes_A1->obj.AngleToLeft = it_item.value().toString();
                            else if (it_item.key().compare("AngleFromRight", Qt::CaseInsensitive) == 0)
                                pRes_A1->obj.AngleFromRight = it_item.value().toString();
                            else if (it_item.key().compare("AngleToRight", Qt::CaseInsensitive) == 0)
                                pRes_A1->obj.AngleToRight = it_item.value().toString();
                            else if (it_item.key().compare("Duration", Qt::CaseInsensitive) == 0)
                                pRes_A1->obj.Duration = it_item.value().toString();
                            else if (it_item.key().compare("VelocityCur", Qt::CaseInsensitive) == 0)
                                pRes_A1->obj.VelocityCur = it_item.value().toString();

                            // 治疗方案
                            else if (it_item.key().compare("recordId", Qt::CaseInsensitive) == 0)
                                pRes_A1->obj.recordId = it_item.value().toString();
                            else if (it_item.key().compare("deviceId", Qt::CaseInsensitive) == 0)
                                pRes_A1->obj.deviceId = it_item.value().toString();

                            // 用户信息
                            else if (it_item.key().compare("patientName", Qt::CaseInsensitive) == 0)
                                pRes_A1->obj.patientName = it_item.value().toString();
                            else if (it_item.key().compare("patientId", Qt::CaseInsensitive) == 0)
                                pRes_A1->obj.patientId = it_item.value().toString();
                            else if (it_item.key().compare("sex", Qt::CaseInsensitive) == 0)
                                pRes_A1->obj.sex = it_item.value().toString();
                            else if (it_item.key().compare("age", Qt::CaseInsensitive) == 0)
                            {
                                pRes_A1->obj.age = it_item.value().toString();
                                pRes_A1->obj.age.replace(pRes_A1->obj.age.indexOf("岁"), 1, "");
                            }

                            // 华唯新协议
                            if (it_item.key().compare("dev_param", Qt::CaseInsensitive) == 0)
                            {
                                QJsonObject object_item_dev = it_item.value().toObject();
                                QStringList list_item_dev = object_item_dev.keys();

                                QJsonObject::iterator it_item_dev = object_item_dev.begin();
                                while (it_item_dev != object_item_dev.end())
                                {
                                    QString dev_key = it_item_dev.key();
                                    QString dev_val = it_item_dev.value().isDouble() ? QString::number(it_item_dev.value().toInt()) : it_item_dev.value().toString();

                                    // 设备训练参数
                                    if (dev_key.compare("TreatType", Qt::CaseInsensitive) == 0)
                                        pRes_A1->obj.TreatType = dev_val;
                                    else if (dev_key.compare("TrainMode", Qt::CaseInsensitive) == 0)
                                        pRes_A1->obj.TrainMode = dev_val;

                                    else if (dev_key.compare("VelocityCur", Qt::CaseInsensitive) == 0)
                                        pRes_A1->obj.VelocityCur = dev_val;
                                    else if (dev_key.compare("VelocityReduction", Qt::CaseInsensitive) == 0)
                                        pRes_A1->obj.VelocityReduction = dev_val;

                                    else if (dev_key.compare("Duration", Qt::CaseInsensitive) == 0)
                                        pRes_A1->obj.Duration = dev_val;
                                    else if (dev_key.compare("RestDuration", Qt::CaseInsensitive) == 0)
                                        pRes_A1->obj.RestDuration = dev_val;

                                    else if (dev_key.compare("AngleFromLeft", Qt::CaseInsensitive) == 0)
                                        pRes_A1->obj.AngleFromLeft = dev_val;
                                    else if (dev_key.compare("AngleToLeft", Qt::CaseInsensitive) == 0)
                                        pRes_A1->obj.AngleToLeft = dev_val;
                                    else if (dev_key.compare("AngleFromRight", Qt::CaseInsensitive) == 0)
                                        pRes_A1->obj.AngleFromRight = dev_val;
                                    else if (dev_key.compare("AngleToRight", Qt::CaseInsensitive) == 0)
                                        pRes_A1->obj.AngleToRight = dev_val;

                                    else if (dev_key.compare("ScrampSensitivityLeft", Qt::CaseInsensitive) == 0)
                                        pRes_A1->obj.ScrampSensitivityLeft = dev_val;
                                    else if (dev_key.compare("ScrampSensitivityRight", Qt::CaseInsensitive) == 0)
                                        pRes_A1->obj.ScrampSensitivityRight = dev_val;

                                    it_item_dev++;
                                }
                            }

                            it_item++;
                        }
                    }
                }
                it++;
            }
        }
    }
    return pRes_A1;
}
