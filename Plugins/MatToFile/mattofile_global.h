#ifndef MATTOFILE_GLOBAL_H
#define MATTOFILE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MATTOFILE_LIBRARY)
#  define MATTOFILESHARED_EXPORT Q_DECL_EXPORT
#else
#  define MATTOFILESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MATTOFILE_GLOBAL_H
