#ifndef PLOTTER2D_GLOBAL_H
#define PLOTTER2D_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PLOTTER2D_LIBRARY)
#  define PLOTTER2DSHARED_EXPORT Q_DECL_EXPORT
#else
#  define PLOTTER2DSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // PLOTTER2D_GLOBAL_H
