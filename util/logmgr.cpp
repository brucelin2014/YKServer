// 2023-03-16, Bruce

#include "logmgr.h"
#include <QDebug>
#include <QDateTime>
#include <QFile>
#include <QDir>

LogMgr::LogMgr(const QString& fileName/* = ""*/)
    : m_fileName(fileName)
{

}

bool LogMgr::WriteLog(const QByteArray& content)
{
    bool bRet = false;
    QDateTime time;
    QString logPath = QString("%1/%2%%3.txt").arg(QDir::currentPath()).arg(m_fileName).arg(time.currentDateTime().toString("yyyyMMdd"));
    QFile file(logPath);
    if (!file.open(QIODevice::ReadWrite))
    {
        qDebug() << "打开失败";
    }

    qint64 pos;
    pos = file.size();
    //重新定位文件输入位置，这里是定位到文件尾端
    file.seek(pos);

    qint64 length = -1;
    QString log = QString("\r\n%1 %2").arg(getTime()).arg(content.data());
    length = file.write(log.toUtf8());

    if (length == -1) // 写入文件失败
    {
        qDebug() << "写入文件失败";
        bRet = false;
    }
    else
    {
        bRet = true;
    }

    file.close();
    return bRet;
}

QString LogMgr::getTime()
{
    QDateTime time;
    return QString("%1").arg(time.currentDateTime().toString("hh:mm:ss"));
}
