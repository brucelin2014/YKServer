// 2023-03-03, Bruce

#ifndef DATAPARSERFACTORY_H
#define DATAPARSERFACTORY_H

#include "interface/IDataParser.h"

// 解析中天平台HTTP返回数据
class DataParserFactory
{
public:
    DataParserFactory();

    static IDataParser* CreateDataParser(const QString& sysCode);
};

#endif // DATAPARSERFACTORY_H
