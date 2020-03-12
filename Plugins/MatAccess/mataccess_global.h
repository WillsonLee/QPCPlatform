#ifndef MATACCESS_GLOBAL_H
#define MATACCESS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MATACCESS_LIBRARY)
#  define MATACCESSSHARED_EXPORT Q_DECL_EXPORT
#else
#  define MATACCESSSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MATACCESS_GLOBAL_H
