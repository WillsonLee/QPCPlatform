#ifndef MATLOADER_GLOBAL_H
#define MATLOADER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MATLOADER_LIBRARY)
#  define MATLOADERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define MATLOADERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MATLOADER_GLOBAL_H
