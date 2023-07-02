// 2023-03-03, Bruce

#ifndef RESPONDOBJ_SL4_H
#define RESPONDOBJ_SL4_H

#include <QObject>
#include "entity/respondobj.h"
#include "entity/responddataobj_sl4.h"
#include "interface/IRespondData.h"

// 返回给web api服务器
class RespondObj_SL4
        : public RespondObj
        , public IRespondData
{
    Q_OBJECT
public:
    RespondObj_SL4();

    RespondDataObj_SL4 obj;

    virtual QString GetRecordId() override { return  obj.recordId; }
    virtual QString GetPatientId() override { return obj.patientId; }
    virtual QByteArray ToJson() override { return obj.ToJson(); }
};

#endif // RESPONDOBJ_SL4_H
