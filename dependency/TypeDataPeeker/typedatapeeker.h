#ifndef TYPEDATAPEEKER_H
#define TYPEDATAPEEKER_H

#include "typedatapeeker_global.h"
#include <QString>
#include <Any.h>

class TYPEDATAPEEKERSHARED_EXPORT TypeDataPeeker
{

public:
    TypeDataPeeker();
    static QString peek(Any data);
private:
    static QString type(Any data);
};

#endif // TYPEDATAPEEKER_H
