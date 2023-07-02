// 2023-07-02, Bruce

#ifndef DATAPARSER_H
#define DATAPARSER_H

#include "entity/respondobj.h"
#include "ZTS_def.h"

// 解析中天平台HTTP返回数据
class DataParser
{
public:
    DataParser();

    virtual RespondObj* ParseData(const QString& respond);

    // 更新医嘱Obj
    bool UpdateObj(QString& obj);
};

#endif // DATAPARSER_H
