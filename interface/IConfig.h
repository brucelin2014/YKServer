// 2023-03-15, Bruce

#ifndef ICONFIG_H
#define ICONFIG_H

#include <QString>

class IConfig
{
public:
    virtual ~IConfig() {}

    virtual const QString& Get_deviceId() = 0;

    virtual const QString& Get_report_folder() = 0;
};

#endif // ICONFIG_H
