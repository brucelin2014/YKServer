// 2023-03-15, Bruce

#ifndef DATA_DEVICE_HEART_H
#define DATA_DEVICE_HEART_H

#include <QObject>
#include "interface/IDataBase_Device.h"
#include "database_device.h"

// 康复设备连接平台数据
class Data_Device_Heart
        : public DataBase_Device
{
    Q_OBJECT
public:
    Data_Device_Heart();

    /// <summary>
    /// 急停状态
    /// 0-正常，急停未被按下
    /// 1-急停已被按下
    /// </summary>
    int ScramStatus;

    /// <summary>
    /// 痉挛状态
    /// 0-未发生痉挛
    /// 1-上肢发生痉挛
    /// 2-下肢发生痉挛
    /// </summary>
    int SpasmStatus;

    /// <summary>
    /// 运动状态
    /// 0-空闲
    /// 1-运动中
    /// 2-暂停
    /// 3-急停
    /// </summary>
    int Status;
};

#endif // DATA_DEVICE_HEART_H
