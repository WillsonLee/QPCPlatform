#ifndef MORPHOLOGY_GLOBAL_H
#define MORPHOLOGY_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MORPHOLOGY_LIBRARY)
#  define MORPHOLOGYSHARED_EXPORT Q_DECL_EXPORT
#else
#  define MORPHOLOGYSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MORPHOLOGY_GLOBAL_H
