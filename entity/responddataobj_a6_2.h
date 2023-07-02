// 2023-06-13, Bruce

#ifndef RESPONDDATAOBJ_A6_2_H
#define RESPONDDATAOBJ_A6_2_H

#include <QObject>
#include "responddatabase.h"

class RespondDataObj_A6_2
        : public RespondDataBase
{
    Q_OBJECT
public:
    RespondDataObj_A6_2();

    QByteArray ToJson();

    bool IsValid();
};

#endif // RESPONDDATAOBJ_A6_2_H
