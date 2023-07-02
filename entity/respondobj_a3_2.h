// 2023-06-16, Bruce

#ifndef RESPONDOBJ_A3_2_H
#define RESPONDOBJ_A3_2_H

#include <QObject>
#include "entity/respondobj.h"
#include "entity/responddataobj_a3_2.h"
#include "interface/IRespondData.h"

class RespondObj_A3_2
        : public RespondObj
        , public IRespondData
{
    Q_OBJECT
public:
    RespondObj_A3_2();

    RespondDataObj_A3_2 obj;

    virtual QString GetRecordId() override { return  obj.recordId; }
    virtual QString GetPatientId() override { return obj.patientId; }
    virtual QByteArray ToJson() override { return obj.ToJson(); }
};

#endif // RESPONDOBJ_A3_2_H
