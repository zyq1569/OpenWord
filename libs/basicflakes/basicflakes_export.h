
#ifndef BASICFLAKES_EXPORT_H
#define BASICFLAKES_EXPORT_H

#ifdef BASICFLAKES_STATIC_DEFINE
#  define BASICFLAKES_EXPORT
#  define BASICFLAKES_NO_EXPORT
#else
#  ifndef BASICFLAKES_EXPORT
#    ifdef basicflakes_EXPORTS
        /* We are building this library */
#      define BASICFLAKES_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define BASICFLAKES_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef BASICFLAKES_NO_EXPORT
#    define BASICFLAKES_NO_EXPORT 
#  endif
#endif

#ifndef BASICFLAKES_DEPRECATED
#  define BASICFLAKES_DEPRECATED __declspec(deprecated)
#endif

#ifndef BASICFLAKES_DEPRECATED_EXPORT
#  define BASICFLAKES_DEPRECATED_EXPORT BASICFLAKES_EXPORT BASICFLAKES_DEPRECATED
#endif

#ifndef BASICFLAKES_DEPRECATED_NO_EXPORT
#  define BASICFLAKES_DEPRECATED_NO_EXPORT BASICFLAKES_NO_EXPORT BASICFLAKES_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef BASICFLAKES_NO_DEPRECATED
#    define BASICFLAKES_NO_DEPRECATED
#  endif
#endif

#endif /* BASICFLAKES_EXPORT_H */
