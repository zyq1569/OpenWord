
#ifndef KOFORMULA_EXPORT_H
#define KOFORMULA_EXPORT_H

#ifdef KOFORMULA_STATIC_DEFINE
#  define KOFORMULA_EXPORT
#  define KOFORMULA_NO_EXPORT
#else
#  ifndef KOFORMULA_EXPORT
#    ifdef koformula_EXPORTS
        /* We are building this library */
#      define KOFORMULA_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define KOFORMULA_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef KOFORMULA_NO_EXPORT
#    define KOFORMULA_NO_EXPORT 
#  endif
#endif

#ifndef KOFORMULA_DEPRECATED
#  define KOFORMULA_DEPRECATED __declspec(deprecated)
#endif

#ifndef KOFORMULA_DEPRECATED_EXPORT
#  define KOFORMULA_DEPRECATED_EXPORT KOFORMULA_EXPORT KOFORMULA_DEPRECATED
#endif

#ifndef KOFORMULA_DEPRECATED_NO_EXPORT
#  define KOFORMULA_DEPRECATED_NO_EXPORT KOFORMULA_NO_EXPORT KOFORMULA_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef KOFORMULA_NO_DEPRECATED
#    define KOFORMULA_NO_DEPRECATED
#  endif
#endif

#endif /* KOFORMULA_EXPORT_H */
