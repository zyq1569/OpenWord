
#ifndef KOODF_EXPORT_H
#define KOODF_EXPORT_H

#ifdef KOODF_STATIC_DEFINE
#  define KOODF_EXPORT
#  define KOODF_NO_EXPORT
#else
#  ifndef KOODF_EXPORT
#    ifdef koodf_EXPORTS
        /* We are building this library */
#      define KOODF_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define KOODF_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef KOODF_NO_EXPORT
#    define KOODF_NO_EXPORT 
#  endif
#endif

#ifndef KOODF_DEPRECATED
#  define KOODF_DEPRECATED __declspec(deprecated)
#endif

#ifndef KOODF_DEPRECATED_EXPORT
#  define KOODF_DEPRECATED_EXPORT KOODF_EXPORT KOODF_DEPRECATED
#endif

#ifndef KOODF_DEPRECATED_NO_EXPORT
#  define KOODF_DEPRECATED_NO_EXPORT KOODF_NO_EXPORT KOODF_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef KOODF_NO_DEPRECATED
#    define KOODF_NO_DEPRECATED
#  endif
#endif

#endif /* KOODF_EXPORT_H */
