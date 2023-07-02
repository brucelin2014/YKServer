// 2023-06-16, Bruce

#ifndef RESPONDOBJ_PS1_H
#define RESPONDOBJ_PS1_H

#include <QObject>
#include "entity/respondobj.h"
#include "entity/responddataobj_ps1.h"
#include "interface/IRespondData.h"

class RespondObj_PS1
        : public RespondObj
        , public IRespondData
{
    Q_OBJECT
public:
    RespondObj_PS1();

    RespondDataObj_PS1 obj;

    virtual QString GetRecordId() override { return  obj.recordId; }
    virtual QString GetPatientId() override { return obj.patientId; }
    virtual QByteArray ToJson() override { return obj.ToJson(); }
};

#endif // RESPONDOBJ_PS1_H
