#ifndef KOMAIN_GLOBAL_H
#define KOMAIN_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(KOMAIN_LIBRARY)
#  define KOMAIN_EXPORT Q_DECL_EXPORT
#else
#  define KOMAIN_EXPORT Q_DECL_IMPORT
#endif

#endif // KOMAIN_GLOBAL_H
