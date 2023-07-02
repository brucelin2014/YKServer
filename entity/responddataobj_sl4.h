// 2023-03-03, Bruce

#ifndef RESPONDDATAOBJ_SL4_H
#define RESPONDDATAOBJ_SL4_H

#include <QObject>
#include "entity/responddatabase.h"
#include "interface/IRespondData.h"

class RespondDataObj_SL4
        : public RespondDataBase
{
    Q_OBJECT
public:
    RespondDataObj_SL4();

    // 训练模式
    // 0-主动
    // 1-被动
    // 2-助力
    QString Mode;

    // 训练程序
    // 0-标准程序
    // 1-放松程序
    // 2-力量和耐力程序
    // 3-协调能力程序
    // 4-训练模式2
    // 5-训练模式3
    // 6-训练模式4
    // 7-守卫家园
    // 8-打水栽花
    // 9-美味餐厅
    // 10-快乐舞蹈
    // 11-极速奔跑
    // 12-极速摩托
    QString Content;

    // 训练部位
    // 0-上肢
    // 1-下肢
    // 2-上下肢
    QString Body;

    QByteArray ToJson();

    bool IsValid();
};

#endif // RESPONDDATAOBJ_SL4_H
