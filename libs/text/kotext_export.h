
#ifndef KOTEXT_EXPORT_H
#define KOTEXT_EXPORT_H

#ifdef KOTEXT_STATIC_DEFINE
#  define KOTEXT_EXPORT
#  define KOTEXT_NO_EXPORT
#else
#  ifndef KOTEXT_EXPORT
#    ifdef kotext_EXPORTS
        /* We are building this library */
#      define KOTEXT_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define KOTEXT_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef KOTEXT_NO_EXPORT
#    define KOTEXT_NO_EXPORT 
#  endif
#endif

#ifndef KOTEXT_DEPRECATED
#  define KOTEXT_DEPRECATED __declspec(deprecated)
#endif

#ifndef KOTEXT_DEPRECATED_EXPORT
#  define KOTEXT_DEPRECATED_EXPORT KOTEXT_EXPORT KOTEXT_DEPRECATED
#endif

#ifndef KOTEXT_DEPRECATED_NO_EXPORT
#  define KOTEXT_DEPRECATED_NO_EXPORT KOTEXT_NO_EXPORT KOTEXT_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef KOTEXT_NO_DEPRECATED
#    define KOTEXT_NO_DEPRECATED
#  endif
#endif

#endif /* KOTEXT_EXPORT_H */
