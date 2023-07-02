// 2023-03-10, Bruce

#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include "interface/ITcpServer_Listener.h"

class TcpServer : public QObject
{
    Q_OBJECT
public:
    TcpServer(QObject* parent, ITcpServer_Listener* pListener, const unsigned short port);
    virtual ~TcpServer();

    bool Send(const QByteArray& data);

private:
    void initServer(const unsigned short port = 8899);
    void closeServer();

    QTcpServer* m_pServer;
    QList<QTcpSocket*> m_clientList;
    ITcpServer_Listener* m_pListener;
    QList<QByteArray> m_datas; // 缓存治疗方案
};

#endif // TCPSERVER_H
