// 2023-07-02, Bruce

#include "jsontools.h"
#include <QJsonDocument>
#include <QDebug>

QString JsonTools::ToString(const QJsonObject& object)
{
    QJsonDocument doc;
    doc.setObject(object);
    QByteArray byteArray = doc.toJson(QJsonDocument::Compact);
    QString strJson(byteArray);
    qDebug() << strJson;
    return strJson;
}

QByteArray JsonTools::ToArray(const QJsonObject& object)
{
    QJsonDocument doc;
    doc.setObject(object);
    QByteArray byteArray = doc.toJson(QJsonDocument::Compact);
    QString strJson(byteArray);
    qDebug() << strJson;
    return byteArray;
}
