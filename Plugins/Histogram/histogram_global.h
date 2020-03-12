#ifndef HISTOGRAM_GLOBAL_H
#define HISTOGRAM_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(HISTOGRAM_LIBRARY)
#  define HISTOGRAMSHARED_EXPORT Q_DECL_EXPORT
#else
#  define HISTOGRAMSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // HISTOGRAM_GLOBAL_H
