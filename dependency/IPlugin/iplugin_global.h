#ifndef IPLUGIN_GLOBAL_H
#define IPLUGIN_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(IPLUGIN_LIBRARY)
#  define IPLUGINSHARED_EXPORT Q_DECL_EXPORT
#else
#  define IPLUGINSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // IPLUGIN_GLOBAL_H
