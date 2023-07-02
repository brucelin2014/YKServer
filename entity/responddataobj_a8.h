// 2023-06-13, Bruce

#ifndef RESPONDDATAOBJ_A8_H
#define RESPONDDATAOBJ_A8_H

#include <QObject>
#include "responddatabase.h"

class RespondDataObj_A8
        : public RespondDataBase
{
    Q_OBJECT
public:
    RespondDataObj_A8();

    QByteArray ToJson();

    bool IsValid();
};

#endif // RESPONDDATAOBJ_A8_H
