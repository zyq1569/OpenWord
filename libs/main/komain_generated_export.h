
#ifndef KOMAIN_EXPORT_H
#define KOMAIN_EXPORT_H

#ifdef KOMAIN_STATIC_DEFINE
#  define KOMAIN_EXPORT
#  define KOMAIN_NO_EXPORT
#else
#  ifndef KOMAIN_EXPORT
#    ifdef komain_EXPORTS
        /* We are building this library */
#      define KOMAIN_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define KOMAIN_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef KOMAIN_NO_EXPORT
#    define KOMAIN_NO_EXPORT 
#  endif
#endif

#ifndef KOMAIN_DEPRECATED
#  define KOMAIN_DEPRECATED __declspec(deprecated)
#endif

#ifndef KOMAIN_DEPRECATED_EXPORT
#  define KOMAIN_DEPRECATED_EXPORT KOMAIN_EXPORT KOMAIN_DEPRECATED
#endif

#ifndef KOMAIN_DEPRECATED_NO_EXPORT
#  define KOMAIN_DEPRECATED_NO_EXPORT KOMAIN_NO_EXPORT KOMAIN_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef KOMAIN_NO_DEPRECATED
#    define KOMAIN_NO_DEPRECATED
#  endif
#endif

#endif /* KOMAIN_EXPORT_H */
