// 2023-06-16, Bruce

#ifndef DATAPARSER_A3_2_H
#define DATAPARSER_A3_2_H

#include "interface/IDataParser.h"

// 解析中天平台HTTP返回数据
class DataParser_A3_2 : public IDataParser
{
public:
    DataParser_A3_2();

    virtual IRespondData* ParseData(const ZTS_API& api, const QString& obj) override;
};

#endif // DATAPARSER_A3_2_H
