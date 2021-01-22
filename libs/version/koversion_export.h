
#ifndef KOVERSION_EXPORT_H
#define KOVERSION_EXPORT_H

#ifdef KOVERSION_STATIC_DEFINE
#  define KOVERSION_EXPORT
#  define KOVERSION_NO_EXPORT
#else
#  ifndef KOVERSION_EXPORT
#    ifdef koversion_EXPORTS
        /* We are building this library */
#      define KOVERSION_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define KOVERSION_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef KOVERSION_NO_EXPORT
#    define KOVERSION_NO_EXPORT 
#  endif
#endif

#ifndef KOVERSION_DEPRECATED
#  define KOVERSION_DEPRECATED __declspec(deprecated)
#endif

#ifndef KOVERSION_DEPRECATED_EXPORT
#  define KOVERSION_DEPRECATED_EXPORT KOVERSION_EXPORT KOVERSION_DEPRECATED
#endif

#ifndef KOVERSION_DEPRECATED_NO_EXPORT
#  define KOVERSION_DEPRECATED_NO_EXPORT KOVERSION_NO_EXPORT KOVERSION_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef KOVERSION_NO_DEPRECATED
#    define KOVERSION_NO_DEPRECATED
#  endif
#endif

#endif /* KOVERSION_EXPORT_H */
