// 2023-03-03, Bruce

#ifndef IRESPONDDATA_H
#define IRESPONDDATA_H

#include <QString>

// 医嘱接口
class IRespondData
{
public:
    virtual ~IRespondData() {}

    virtual QString GetRecordId() = 0;

    virtual QString GetPatientId() = 0;

    virtual QByteArray ToJson() = 0;
};

#endif // IRESPONDDATA_H
