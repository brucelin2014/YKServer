// 2023-06-13, Bruce

#ifndef RESPONDDATAOBJ_A3_2_H
#define RESPONDDATAOBJ_A3_2_H

#include <QObject>
#include "responddatabase.h"

class RespondDataObj_A3_2
        : public RespondDataBase
{
    Q_OBJECT
public:
    RespondDataObj_A3_2();

    QByteArray ToJson();

    bool IsValid();
};

#endif // RESPONDDATAOBJ_A3_2_H
