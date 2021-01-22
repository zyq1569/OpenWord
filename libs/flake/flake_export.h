
#ifndef FLAKE_EXPORT_H
#define FLAKE_EXPORT_H

#ifdef FLAKE_STATIC_DEFINE
#  define FLAKE_EXPORT
#  define FLAKE_NO_EXPORT
#else
#  ifndef FLAKE_EXPORT
#    ifdef flake_EXPORTS
        /* We are building this library */
#      define FLAKE_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define FLAKE_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef FLAKE_NO_EXPORT
#    define FLAKE_NO_EXPORT 
#  endif
#endif

#ifndef FLAKE_DEPRECATED
#  define FLAKE_DEPRECATED __declspec(deprecated)
#endif

#ifndef FLAKE_DEPRECATED_EXPORT
#  define FLAKE_DEPRECATED_EXPORT FLAKE_EXPORT FLAKE_DEPRECATED
#endif

#ifndef FLAKE_DEPRECATED_NO_EXPORT
#  define FLAKE_DEPRECATED_NO_EXPORT FLAKE_NO_EXPORT FLAKE_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef FLAKE_NO_DEPRECATED
#    define FLAKE_NO_DEPRECATED
#  endif
#endif

#endif /* FLAKE_EXPORT_H */
