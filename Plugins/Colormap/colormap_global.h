#ifndef COLORMAP_GLOBAL_H
#define COLORMAP_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(COLORMAP_LIBRARY)
#  define COLORMAPSHARED_EXPORT Q_DECL_EXPORT
#else
#  define COLORMAPSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // COLORMAP_GLOBAL_H
