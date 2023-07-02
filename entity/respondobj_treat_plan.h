// 2023-07-02, Bruce

#ifndef RESPONDOBJ_Treat_Plan_H
#define RESPONDOBJ_Treat_Plan_H

#include <QObject>
#include "entity/responddatabase.h"
#include "interface/IRespondData.h"
#include "entity/respondobj.h"

class RespondObj_Treat_Plan
        : public RespondObj
        , public IRespondData // 医嘱接口
{
    Q_OBJECT
public:
    RespondObj_Treat_Plan();

    RespondDataBase obj;

    virtual QString GetRecordId() override { return  obj.recordId; }
    virtual QString GetPatientId() override { return obj.patientId; }
    virtual QByteArray ToJson() override;
};

#endif // RESPONDOBJ_Treat_Plan_H
