// 2023-03-16, Bruce

#ifndef LOGMGR_H
#define LOGMGR_H

#include <QObject>

class LogMgr
{
public:
    LogMgr(const QString& fileName = "");

    bool WriteLog(const QByteArray& content);

private:
    QString getTime();
    QString m_fileName;
};

#endif // LOGMGR_H
