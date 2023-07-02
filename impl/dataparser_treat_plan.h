// 2023-06-16, Bruce

#ifndef DATAPARSER_Treat_Plan_H
#define DATAPARSER_Treat_Plan_H

#include "interface/IDataParser.h"

// 解析中天平台HTTP返回数据
class DataParser_Treat_Plan : public IDataParser
{
public:
    DataParser_Treat_Plan();

    virtual IRespondData* ParseData(const ZTS_API& api, const QString& obj) override;
};

#endif // DATAPARSER_Treat_Plan_H
