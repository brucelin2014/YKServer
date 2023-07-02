// 2023-06-16, Bruce

#ifndef DATAPARSER_A1_H
#define DATAPARSER_A1_H

#include "interface/IDataParser.h"

// 解析中天平台HTTP返回数据
class DataParser_A1 : public IDataParser
{
public:
    DataParser_A1();

    virtual IRespondData* ParseData(const ZTS_API& api, const QString& respond) override;
};

#endif // DATAPARSER_A1_H
