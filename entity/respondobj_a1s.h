// 2023-03-03, Bruce

#ifndef RESPONDOBJ_A1S_H
#define RESPONDOBJ_A1S_H

#include <QObject>
#include "entity/respondobj.h"
#include "entity/responddataobj_a1s.h"
#include "interface/IRespondData.h"

class RespondObj_A1S
        : public RespondObj
        , public IRespondData
{
    Q_OBJECT
public:
    RespondObj_A1S();

    RespondDataObj_A1S obj;

    virtual QString GetRecordId() override { return  obj.recordId; }
    virtual QString GetPatientId() override { return obj.patientId; }
    virtual QByteArray ToJson() override { return obj.ToJson(); }
};

#endif // RESPONDOBJ_A1S_H
