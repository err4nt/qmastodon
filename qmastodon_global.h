#ifndef QMASTODON_GLOBAL_H
#define QMASTODON_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QMASTODON_LIBRARY)
#  define QMASTODONSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QMASTODONSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QMASTODON_GLOBAL_H
