// 2023-03-10, Bruce

#include "tcpserver.h"
#include <QHostAddress>

TcpServer::TcpServer(QObject* parent, ITcpServer_Listener* pListener, const unsigned short port)
    : QObject(parent)
    , m_pListener(pListener)
{
    initServer(port);
}

TcpServer::~TcpServer()
{
    closeServer();
}

void TcpServer::initServer(const unsigned short port)
{
    m_pServer = new QTcpServer(this);
    if (m_pServer->isListening())
    {
        closeServer();
    }
    else
    {
        const QHostAddress address = QHostAddress::Any;
        m_pServer->listen(address, port);
    }

    connect(m_pServer, &QTcpServer::newConnection, this, [this] {
        while (m_pServer->hasPendingConnections())
        {
            QTcpSocket *socket = m_pServer->nextPendingConnection();
            m_clientList.append(socket);
            if (m_pListener != nullptr)
                m_pListener->newConnection(socket->peerAddress().toString(), socket->peerPort());

            connect(socket, &QTcpSocket::readyRead, [this, socket] {
                if (socket->bytesAvailable() <= 0)
                    return;

                if (m_pListener != nullptr)
                    m_pListener->readyRead(QString::fromUtf8(socket->readAll()), socket->peerAddress().toString(), socket->peerPort());
            });

            //error信号在5.15换了名字
#if QT_VERSION < QT_VERSION_CHECK(5, 15, 0)
            //错误信息
            connect(socket, static_cast<void(QAbstractSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error),
                    [this, socket](QAbstractSocket::SocketError) {
                if (m_pListener != nullptr)
                    m_pListener->SocketError(socket->errorString(), socket->peerAddress().toString(), socket->peerPort());
            });
#else
            //错误信息
            connect(socket, &QAbstractSocket::errorOccurred, [this,socket](QAbstractSocket::SocketError){
                if (m_pListener != nullptr)
                    m_pListener->SocketError(socket->errorString(), socket->peerAddress().toString(), socket->peerPort());
            });
#endif

            //连接断开，销毁socket对象，这是为了开关server时socket正确释放
            connect(socket, &QTcpSocket::disconnected, [this, socket] {
                socket->deleteLater();
                m_clientList.removeOne(socket);
                if (m_pListener != nullptr)
                    m_pListener->disconnected(socket->peerAddress().toString(), socket->peerPort());
            });
        }
    });

    //server的错误信息
    connect(m_pServer, &QTcpServer::acceptError, [this](QAbstractSocket::SocketError) {
        if (m_pListener != nullptr)
            m_pListener->acceptError(m_pServer->errorString());
    });
}

bool TcpServer::Send(const QByteArray& data)
{
    // 前面插入
    if (data.isEmpty())
        return false;

    m_datas.push_front(data);

    if (!m_pServer->isListening())
        return false;

    // 后面开始释放
    int size = m_datas.size();
    for (int i = size - 1; i >= 0 ; i--)
    {
        auto iter = m_datas[i];
        bool bRet = false;
        for (QTcpSocket *socket : m_clientList)
        {
            int len = socket->write(data);
            if (len > 0)
                bRet = true;
            //socket->waitForBytesWritten();
        }
        if (bRet)
            m_datas.pop_back();
    }
    return true;
}

void TcpServer::closeServer()
{
    if (m_pServer != nullptr)
        m_pServer->close();

    for (QTcpSocket * socket : m_clientList)
    {
        socket->disconnectFromHost();
        if (socket->state() != QAbstractSocket::UnconnectedState)
        {
            socket->abort();
        }
    }
}
