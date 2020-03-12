#ifndef RANDOMGENERATOR_GLOBAL_H
#define RANDOMGENERATOR_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(RANDOMGENERATOR_LIBRARY)
#  define RANDOMGENERATORSHARED_EXPORT Q_DECL_EXPORT
#else
#  define RANDOMGENERATORSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // RANDOMGENERATOR_GLOBAL_H