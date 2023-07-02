// 2023-06-16, Bruce

#ifndef DATAPARSER_PS1_H
#define DATAPARSER_PS1_H

#include "interface/IDataParser.h"

// 解析中天平台HTTP返回数据
class DataParser_PS1 : public IDataParser
{
public:
    DataParser_PS1();

    virtual IRespondData* ParseData(const ZTS_API& api, const QString& obj) override;
};

#endif // DATAPARSER_PS1_H
