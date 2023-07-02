// 2023-03-03, Bruce

#ifndef RESPONDOBJ_H
#define RESPONDOBJ_H

#include <QObject>

// 物联平台回复数据包格式
class RespondObj : public QObject
{
    Q_OBJECT
public:
    RespondObj();

    int code;
    QString msg;
    int total;

    QString obj;
    QString status; // 治疗状态，0:待治疗；1:开始治疗；2：结束治疗;3：暂停治疗
};

#endif // RESPONDOBJ_H
