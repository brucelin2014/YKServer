// 2023-06-13, Bruce

#ifndef RESPONDDATAOBJ_A1_H
#define RESPONDDATAOBJ_A1_H

#include <QObject>
#include "responddatabase.h"

class RespondDataObj_A1
        : public RespondDataBase
{
    Q_OBJECT
public:
    RespondDataObj_A1();

    QString TreatType; // 0-评估, 1-训练
    QString TrainMode; // 0-被动模式, 1-主被动模式

    /// <summary>
    /// 踏步速度
    /// </summary>
    QString VelocityCur;
    QString VelocityReduction; // 速度降低值

    /// <summary>
    /// 治疗时间
    /// </summary>
    QString Duration;
    QString RestDuration; // 休息时间

    QString AngleFromLeft; // 左腿踏步角度开始
    QString AngleToLeft;   // 左腿踏步角度结束
    QString AngleFromRight; // 右腿踏步角度开始
    QString AngleToRight;   // 右腿踏步角度结束

    QString ScrampSensitivityLeft;  // 左腿痉挛灵敏度
    QString ScrampSensitivityRight; // 右腿痉挛灵敏度

    QByteArray ToJson();

    bool IsValid();
};

#endif // RESPONDDATAOBJ_A1_H
