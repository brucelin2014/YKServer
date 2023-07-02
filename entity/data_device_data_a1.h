// 2023-06-13, Bruce

#ifndef DATA_DEVICE_DATA_A1_H
#define DATA_DEVICE_DATA_A1_H

#include <QObject>
#include "interface/IDataBase_Device.h"
#include "database_device.h"


// 康复设备连接平台数据, A1-3, A1-3S, A1-2, A1-2S
class Data_Device_Data_A1
        : public DataBase_Device
{
    Q_OBJECT
public:
    Data_Device_Data_A1();

    /// <summary>
    /// 运动状态
    /// 0-空闲
    /// 1-运动中
    /// 2-暂停
    /// 3-急停
    /// </summary>
    int Status = 0;

    int TreatType = 1; // 0-评估, 1-训练
    int TrainMode = 0; // 0-被动模式, 1-主被动模式

    /// <summary>
    /// 踏步速度
    /// </summary>
    int VelocityCur = 20;
    int VelocityReduction = 1; // 速度降低值

    /// <summary>
    /// 治疗时间
    /// </summary>
    int Duration = 30;
    int RestDuration = 10; // 休息时间

    int AngleFromLeft = 2; // 左腿踏步角度开始
    int AngleToLeft = 20;   // 左腿踏步角度结束
    int AngleFromRight = 2; // 右腿踏步角度开始
    int AngleToRight = 20;   // 右腿踏步角度结束

    int ScrampSensitivityLeft = 40;  // 左腿痉挛灵敏度
    int ScrampSensitivityRight = 40; // 右腿痉挛灵敏度

    QString patientName;
    QString patientId;
    QString sex;
    QString age;

    QString recordId;

    QByteArray ToJson();
};

#endif // DATA_DEVICE_DATA_A1_H
