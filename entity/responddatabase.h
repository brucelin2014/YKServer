// 2023-03-03, Bruce

#ifndef RESPONDDATABASE_H
#define RESPONDDATABASE_H

#include <QObject>
#include "patientobj.h"

// 治疗方案返回数据
class RespondDataBase : public PatientObj // 患者信息
{
    Q_OBJECT
public:
    RespondDataBase();

    QString recordId;
    QString deviceId;
};

#endif // RESPONDDATABASE_H
