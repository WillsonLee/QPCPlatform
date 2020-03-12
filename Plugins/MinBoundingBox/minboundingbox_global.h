#ifndef MINBOUNDINGBOX_GLOBAL_H
#define MINBOUNDINGBOX_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MINBOUNDINGBOX_LIBRARY)
#  define MINBOUNDINGBOXSHARED_EXPORT Q_DECL_EXPORT
#else
#  define MINBOUNDINGBOXSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MINBOUNDINGBOX_GLOBAL_H