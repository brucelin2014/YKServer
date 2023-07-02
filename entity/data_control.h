// 2023-06-30, Bruce

#ifndef DATA_CONTROL_H
#define DATA_CONTROL_H

#include <QObject>
#include <QString>
#include "interface/IDataBase_Device.h"
#include "database_device.h"


// 康复设备远程控制
class Data_Control
        : public DataBase_Device
{
    Q_OBJECT
public:
    Data_Control();

    /// <summary>
    /// 治疗状态
    /// 0:待治疗；1:开始治疗；2：结束治疗;3：暂停治疗
    QString Status = "0";

    QByteArray ToJson();
};

#endif // DATA_DEVICE_DATA_A1_H
