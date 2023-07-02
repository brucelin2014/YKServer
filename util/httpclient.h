// 2023-02-27, Bruce

#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <QObject>
#include "interface/IZTServer_api_Listener.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>

class HttpClient : public QObject
{
    Q_OBJECT

public:
    HttpClient(IZTServer_api_Listener* pListener, QObject* parent);
    virtual ~HttpClient();

    bool Get(const QString& url);
    bool Post(const QString& url, const QByteArray& array);
    bool Post_PDF(const QString& url, const QString& filePath);
    void SetParentThread(QThread* pThread);

private:
    IZTServer_api_Listener* m_pListener;
    QNetworkAccessManager m_netAccessMgr;
    QNetworkRequest m_httpRequest;
    QFile* m_pFile;

    void CloseFile();

protected slots:
    void finished_request(QNetworkReply *reply);
};

#endif // HTTPCLIENT_H
