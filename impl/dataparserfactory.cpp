// 2023-03-03, Bruce

#include "dataparserfactory.h"
#include "dataparser_a1s.h"
#include "dataparser_sl4.h"
#include "dataparser_a1.h"
#include "dataparser_a3_2.h"
#include "dataparser_a6_2.h"
#include "dataparser_a8.h"
#include "dataparser_ps1.h"

DataParserFactory::DataParserFactory()
{

}

// 解析中天平台HTTP返回数据
IDataParser* DataParserFactory::CreateDataParser(const QString& sysCode)
{
    if (sysCode == "YKA1S")
        return new DataParser_A1S();
    else if (sysCode == "YKSL4" || sysCode == "YKSL4I")
        return new DataParser_SL4();
    else if (sysCode == "YKA1" || sysCode == "YKA1-3S")
        return new DataParser_A1();
    else if (sysCode == "YKA3-2" || sysCode == "YKA3-2S")
        return new DataParser_A3_2();
    else if (sysCode == "YKA6-2" || sysCode == "YKA6" || sysCode == "YKA6-2S")
        return new DataParser_A6_2();
    else if (sysCode == "YKA8")
        return new DataParser_A8();
    else if (sysCode == "YKPS1" || sysCode == "YKPS2")
        return new DataParser_PS1();
    return nullptr;
}
