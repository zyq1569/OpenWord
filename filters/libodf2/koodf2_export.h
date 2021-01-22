
#ifndef KOODF2_EXPORT_H
#define KOODF2_EXPORT_H

#ifdef KOODF2_STATIC_DEFINE
#  define KOODF2_EXPORT
#  define KOODF2_NO_EXPORT
#else
#  ifndef KOODF2_EXPORT
#    ifdef koodf2_EXPORTS
        /* We are building this library */
#      define KOODF2_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define KOODF2_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef KOODF2_NO_EXPORT
#    define KOODF2_NO_EXPORT 
#  endif
#endif

#ifndef KOODF2_DEPRECATED
#  define KOODF2_DEPRECATED __declspec(deprecated)
#endif

#ifndef KOODF2_DEPRECATED_EXPORT
#  define KOODF2_DEPRECATED_EXPORT KOODF2_EXPORT KOODF2_DEPRECATED
#endif

#ifndef KOODF2_DEPRECATED_NO_EXPORT
#  define KOODF2_DEPRECATED_NO_EXPORT KOODF2_NO_EXPORT KOODF2_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef KOODF2_NO_DEPRECATED
#    define KOODF2_NO_DEPRECATED
#  endif
#endif

#endif /* KOODF2_EXPORT_H */
