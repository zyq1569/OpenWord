
#ifndef EASYLOG_EXPORT_H
#define EASYLOG_EXPORT_H

#ifdef KOSTORE_STATIC_DEFINE
#  define KOSTORE_EXPORT
#  define KOSTORE_NO_EXPORT
#else
#  ifndef KOSTORE_EXPORT
#    ifdef easylog_EXPORTS
        /* We are building this library */
#      define KOSTORE_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define KOSTORE_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef KOSTORE_NO_EXPORT
#    define KOSTORE_NO_EXPORT 
#  endif
#endif

#ifndef KOSTORE_DEPRECATED
#  define KOSTORE_DEPRECATED __declspec(deprecated)
#endif

#ifndef KOSTORE_DEPRECATED_EXPORT
#  define KOSTORE_DEPRECATED_EXPORT KOSTORE_EXPORT KOSTORE_DEPRECATED
#endif

#ifndef KOSTORE_DEPRECATED_NO_EXPORT
#  define KOSTORE_DEPRECATED_NO_EXPORT KOSTORE_NO_EXPORT KOSTORE_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef KOSTORE_NO_DEPRECATED
#    define KOSTORE_NO_DEPRECATED
#  endif
#endif

#endif /* KOSTORE_EXPORT_H */
