// 2023-03-15, Bruce

#ifndef DATA_DEVICE_RESPOND_H
#define DATA_DEVICE_RESPOND_H

#include <QObject>
#include "interface/IDataBase_Device.h"
#include "entity/database_device.h"

// 康复设备连接平台数据
class Data_Device_Respond
        : public DataBase_Device
{
    Q_OBJECT
public:
    Data_Device_Respond();

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

#endif // DATA_DEVICE_RESPOND_H
