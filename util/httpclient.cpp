// 2023-02-27, Bruce

#include "httpclient.h"
#include <QEventLoop>

#include <QJsonObject>
#include <QJsonDocument>
#include <QHttpMultiPart>
#include <QFile>
#include "log.h"

HttpClient::HttpClient(IZTServer_api_Listener* pListener, QObject* parent)
    : QObject(parent)
    , m_pListener(pListener)
    , m_netAccessMgr(nullptr)
    , m_pFile(nullptr)
{
    QObject::connect(&m_netAccessMgr, SIGNAL(finished(QNetworkReply*)), this, SLOT(finished_request(QNetworkReply*)));
}

HttpClient::~HttpClient()
{
    CloseFile();
}

void HttpClient::SetParentThread(QThread* pThread)
{
    if (pThread != nullptr)
        m_netAccessMgr.moveToThread(pThread);
}

void HttpClient::CloseFile()
{
    if (m_pFile != nullptr)
    {
        m_pFile->close();
        delete m_pFile;
        m_pFile = nullptr;
    }
}

bool HttpClient::Get(const QString& url)
{
    m_httpRequest.setUrl(QUrl(url));
    m_httpRequest.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/json;charset=utf-8"));
    QNetworkReply* reply = m_netAccessMgr.get(m_httpRequest);

    //开启事件循环，直到请求完成
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    //disconnect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);

    return true;
}

bool HttpClient::Post(const QString& url, const QByteArray& array)
{
    m_httpRequest.setUrl(QUrl(url));
    m_httpRequest.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/json;charset=utf-8"));
    QNetworkReply* reply = m_netAccessMgr.post(m_httpRequest, array);

    //开启事件循环，直到请求完成
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    //disconnect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);

    return true;
}

bool HttpClient::Post_PDF(const QString& url, const QString& filePath)
{
    QHttpMultiPart multiPart(QHttpMultiPart::FormDataType);

    CloseFile();

    m_pFile = new QFile(filePath);
    if (!m_pFile->open(QFile::ReadOnly))
    {
        Log::instance()->error(QString("Open file fail: %1").arg(filePath));
        return false;
    }

    QHttpPart filePart;
    filePart.setBodyDevice(m_pFile);//这里的file对象就是我们需要提交的文件，如果需要上传多个文件，我们就需要创建多个QHttpPart对象
    filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/pdf"));
    multiPart.append(filePart);

    m_httpRequest.setUrl(QUrl(url));
    m_httpRequest.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/pdf"));
    QNetworkReply* reply = m_netAccessMgr.post(m_httpRequest, &multiPart);

    //开启事件循环，直到请求完成
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    //disconnect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);

    return true;
}

void HttpClient::finished_request(QNetworkReply *reply)
{
    int iError = reply->error();
    if (iError == QNetworkReply::NoError)
    {
        CloseFile();

        QByteArray bytes = reply->readAll();
        QString string = QString::fromUtf8(bytes);
        if (m_pListener != nullptr)
            m_pListener->OnRespond(reply->url().url(), string);
        Log::instance()->info(QString("finished_request: %1\n%2").arg(reply->url().url()).arg(string));
    }
    else
    {
        if (m_pListener != nullptr)
            m_pListener->OnError(reply->url().url(), iError);
        Log::instance()->error(QString("Http request error: %1\nerror code: %2").arg(reply->url().url()).arg(iError));
    }
    reply->deleteLater();
}
