// 2023-03-11, Bruce

#ifndef IZTSERVER_TCP_LISTENER_H
#define IZTSERVER_TCP_LISTENER_H

#include <QString>

class IZTServer_tcp_Listener
{
public:
    virtual ~IZTServer_tcp_Listener() {}

    // 获取返回结果
    virtual void OnRespond(const QString& urlRequest, const QString& respond) = 0;

};

#endif // IZTSERVER_TCP_LISTENER_H
