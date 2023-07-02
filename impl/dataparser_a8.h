// 2023-06-16, Bruce

#ifndef DATAPARSER_A8_H
#define DATAPARSER_A8_H

#include "interface/IDataParser.h"

// 解析中天平台HTTP返回数据
class DataParser_A8 : public IDataParser
{
public:
    DataParser_A8();

    virtual IRespondData* ParseData(const ZTS_API& api, const QString& respond) override;
};

#endif // DATAPARSER_A8_H
