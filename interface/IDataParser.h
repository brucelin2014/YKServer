// 2023-03-03, Bruce

#ifndef IDATAPARSER_H
#define IDATAPARSER_H

#include <QString>
#include "ZTS_def.h"
#include "IRespondData.h"

class IDataParser
{
public:
    virtual ~IDataParser() {}

    virtual IRespondData* ParseData(const ZTS_API& api, const QString& obj) = 0;
};

#endif // IDATAPARSER_H
