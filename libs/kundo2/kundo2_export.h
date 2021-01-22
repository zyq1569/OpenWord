
#ifndef KUNDO2_EXPORT_H
#define KUNDO2_EXPORT_H

#ifdef KUNDO2_STATIC_DEFINE
#  define KUNDO2_EXPORT
#  define KUNDO2_NO_EXPORT
#else
#  ifndef KUNDO2_EXPORT
#    ifdef kundo2_EXPORTS
        /* We are building this library */
#      define KUNDO2_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define KUNDO2_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef KUNDO2_NO_EXPORT
#    define KUNDO2_NO_EXPORT 
#  endif
#endif

#ifndef KUNDO2_DEPRECATED
#  define KUNDO2_DEPRECATED __declspec(deprecated)
#endif

#ifndef KUNDO2_DEPRECATED_EXPORT
#  define KUNDO2_DEPRECATED_EXPORT KUNDO2_EXPORT KUNDO2_DEPRECATED
#endif

#ifndef KUNDO2_DEPRECATED_NO_EXPORT
#  define KUNDO2_DEPRECATED_NO_EXPORT KUNDO2_NO_EXPORT KUNDO2_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef KUNDO2_NO_DEPRECATED
#    define KUNDO2_NO_DEPRECATED
#  endif
#endif

#endif /* KUNDO2_EXPORT_H */
