#ifndef QTPCLVIEWER_GLOBAL_H
#define QTPCLVIEWER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QTPCLVIEWER_LIBRARY)
#  define QTPCLVIEWERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QTPCLVIEWERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QTPCLVIEWER_GLOBAL_H
