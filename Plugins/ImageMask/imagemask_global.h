#ifndef IMAGEMASK_GLOBAL_H
#define IMAGEMASK_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(IMAGEMASK_LIBRARY)
#  define IMAGEMASKSHARED_EXPORT Q_DECL_EXPORT
#else
#  define IMAGEMASKSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // IMAGEMASK_GLOBAL_H
