// 2023-03-03, Bruce

#ifndef RESPONDDATAOBJ_A1S_H
#define RESPONDDATAOBJ_A1S_H

#include <QObject>
#include "responddatabase.h"

class RespondDataObj_A1S
        : public RespondDataBase
{
    Q_OBJECT
public:
    RespondDataObj_A1S();

    QString AngleFromLeft;  // 左腿踏步角度开始
    QString AngleToLeft;    // 左腿踏步角度结束
    QString AngleFromRight; // 右腿踏步角度开始
    QString AngleToRight;   // 右腿踏步角度结束
    QString Duration;       // 治疗时间
    QString VelocityCur;    // 踏步速度

    QByteArray ToJson();

    bool IsValid();
};

#endif // RESPONDDATAOBJ_A1S_H
