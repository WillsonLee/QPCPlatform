#ifndef TYPEDATAPEEKER_GLOBAL_H
#define TYPEDATAPEEKER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(TYPEDATAPEEKER_LIBRARY)
#  define TYPEDATAPEEKERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define TYPEDATAPEEKERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // TYPEDATAPEEKER_GLOBAL_H
