// 2023-07-02, Bruce

#ifndef JSONTOOLS_H
#define JSONTOOLS_H

#include <QString>
#include <QJsonObject>

class JsonTools
{
public:
    static QString ToString(const QJsonObject& object);
    static QByteArray ToArray(const QJsonObject& object);
};

#endif // JSONTOOLS_H
