// 2023-06-29, Bruce

#include "qstringtools.h"

uint QStringTools::String2Uint(const QString& str)
{
    return str.isEmpty() ? 0 : str.toUInt();
}
