#ifndef PCDLOADER_GLOBAL_H
#define PCDLOADER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PCDLOADER_LIBRARY)
#  define PCDLOADERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define PCDLOADERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // PCDLOADER_GLOBAL_H
