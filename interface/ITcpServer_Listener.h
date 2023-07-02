// 2023-03-10, Bruce

#ifndef ITCPSERVER_LISTENER_H
#define ITCPSERVER_LISTENER_H

#include <QString>

class ITcpServer_Listener
{
public:
    virtual ~ITcpServer_Listener() {}

    virtual void newConnection(const QString& peerAddress, const quint16& peerPort) = 0;

    virtual void readyRead(const QString& rev, const QString& peerAddress, const quint16& peerPort) = 0;

    virtual void SocketError(const QString& err, const QString& peerAddress, const quint16& peerPort) = 0;

    virtual void disconnected(const QString& peerAddress, const quint16& peerPort) = 0;

    virtual void acceptError(const QString& err) = 0;
};

#endif // ITCPSERVER_LISTENER_H
