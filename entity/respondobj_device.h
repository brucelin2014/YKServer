// 2023-03-15, Bruce

#ifndef RESPONDOBJ_DEVICE_H
#define RESPONDOBJ_DEVICE_H

#include <QObject>

class RespondObj_Device : public QObject
{
    Q_OBJECT
public:
    RespondObj_Device();

    /// <summary>
    /// 控制指令
    /// 0 - 失败
    /// 1 - 成功
    /// </summary>
    int Code;

    /// <summary>
    /// 返回消息
    /// 成功 / 参数错误
    /// </summary>
    QString Msg;
};

#endif // RESPONDOBJ_DEVICE_H
