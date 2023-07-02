// 2023-03-03, Bruce

#ifndef DATAPARSER_SL4_H
#define DATAPARSER_SL4_H

#include "interface/IDataParser.h"

// 解析中天平台HTTP返回数据
class DataParser_SL4 : public IDataParser
{
public:
    DataParser_SL4();

    virtual IRespondData* ParseData(const ZTS_API& api, const QString& respond) override;
};

#endif // DATAPARSER_SL4_H
