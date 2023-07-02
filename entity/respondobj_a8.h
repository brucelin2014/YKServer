// 2023-06-16, Bruce

#ifndef RESPONDOBJ_A8_H
#define RESPONDOBJ_A8_H

#include <QObject>
#include "entity/respondobj.h"
#include "entity/responddataobj_a8.h"
#include "interface/IRespondData.h"

class RespondObj_A8
        : public RespondObj
        , public IRespondData
{
    Q_OBJECT
public:
    RespondObj_A8();

    RespondDataObj_A8 obj;
    QString status; // 治疗状态，0:待治疗；1:开始治疗；2：结束治疗;3：暂停治疗

    virtual QString GetRecordId() override { return  obj.recordId; }
    virtual QString GetPatientId() override { return obj.patientId; }
    virtual QByteArray ToJson() override { return obj.ToJson(); }
};

#endif // RESPONDOBJ_A8_H
