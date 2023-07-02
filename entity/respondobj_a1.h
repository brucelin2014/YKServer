// 2023-06-16, Bruce

#ifndef RESPONDOBJ_A1_H
#define RESPONDOBJ_A1_H

#include <QObject>
#include "entity/respondobj.h"
#include "entity/responddataobj_a1.h"
#include "interface/IRespondData.h"

class RespondObj_A1
        : public RespondObj
        , public IRespondData // 医嘱接口
{
    Q_OBJECT
public:
    RespondObj_A1();

    RespondDataObj_A1 obj;

    virtual QString GetRecordId() override { return  obj.recordId; }
    virtual QString GetPatientId() override { return obj.patientId; }
    virtual QByteArray ToJson() override { return obj.ToJson(); }
};

#endif // RESPONDOBJ_A1_H
