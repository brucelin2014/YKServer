// 2023-06-13, Bruce

#ifndef RESPONDDATAOBJ_PS1_H
#define RESPONDDATAOBJ_PS1_H

#include <QObject>
#include "responddatabase.h"

class RespondDataObj_PS1
        : public RespondDataBase
{
    Q_OBJECT
public:
    RespondDataObj_PS1();

    QByteArray ToJson();

    bool IsValid();
};

#endif // RESPONDDATAOBJ_PS1_H
