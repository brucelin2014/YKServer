// 2023-02-27, Bruce

#ifndef IZTSERVER_API_LISTENER_H
#define IZTSERVER_API_LISTENER_H

#include <QString>

class IZTServer_api_Listener
{
public:
    virtual ~IZTServer_api_Listener() {}

    // 返回结果
    virtual void OnRespond(const QString& urlRequest, const QString& respond) = 0;

    // 返回错误代码
    virtual void OnError(const QString& urlRequest, const int& errorCode) = 0;

};

#endif // IZTSERVER_API_LISTENER_H
