// 2023-03-03, Bruce

#ifndef DATAPARSER_A1S_H
#define DATAPARSER_A1S_H

#include "interface/IDataParser.h"

// 解析中天平台HTTP返回数据
class DataParser_A1S : public IDataParser
{
public:
    DataParser_A1S();

    virtual IRespondData* ParseData(const ZTS_API& api, const QString& respond) override;
};

#endif // DATAPARSER_A1S_H
