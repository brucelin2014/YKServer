// 2023-04-06, Bruce

#ifndef DATA_DEVICE_DATA_SL4_H
#define DATA_DEVICE_DATA_SL4_H

#include <QObject>
#include "interface/IDataBase_Device.h"
#include "database_device.h"


// 康复设备连接平台数据
class Data_Device_Data_SL4
        : public DataBase_Device
{
    Q_OBJECT
public:
    Data_Device_Data_SL4();

    /// <summary>
    /// 运动状态
    /// 0-空闲
    /// 1-运动中
    /// 2-暂停
    /// 3-急停
    /// </summary>
    int Status;

    // 训练模式
    // 0-主动
    // 1-被动
    // 2-助力
    QString Mode;

    // 训练程序
    // 0-标准程序
    // 1-放松程序
    // 2-力量和耐力程序
    // 3-协调能力程序
    // 4-训练模式2
    // 5-训练模式3
    // 6-训练模式4
    // 7-守卫家园
    // 8-打水栽花
    // 9-美味餐厅
    // 10-快乐舞蹈
    // 11-极速奔跑
    // 12-极速摩托
    QString Content;

    // 训练部位
    // 0-上肢
    // 1-下肢
    // 2-上下肢
    QString Body;

    QString patientName;
    QString patientId;
    QString sex;
    QString age;

    QString recordId;

    QByteArray ToJson();
};

#endif // DATA_DEVICE_DATA_SL4_H
