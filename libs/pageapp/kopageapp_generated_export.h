
#ifndef KOPAGEAPP_EXPORT_H
#define KOPAGEAPP_EXPORT_H

#ifdef KOPAGEAPP_STATIC_DEFINE
#  define KOPAGEAPP_EXPORT
#  define KOPAGEAPP_NO_EXPORT
#else
#  ifndef KOPAGEAPP_EXPORT
#    ifdef kopageapp_EXPORTS
        /* We are building this library */
#      define KOPAGEAPP_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define KOPAGEAPP_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef KOPAGEAPP_NO_EXPORT
#    define KOPAGEAPP_NO_EXPORT 
#  endif
#endif

#ifndef KOPAGEAPP_DEPRECATED
#  define KOPAGEAPP_DEPRECATED __declspec(deprecated)
#endif

#ifndef KOPAGEAPP_DEPRECATED_EXPORT
#  define KOPAGEAPP_DEPRECATED_EXPORT KOPAGEAPP_EXPORT KOPAGEAPP_DEPRECATED
#endif

#ifndef KOPAGEAPP_DEPRECATED_NO_EXPORT
#  define KOPAGEAPP_DEPRECATED_NO_EXPORT KOPAGEAPP_NO_EXPORT KOPAGEAPP_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef KOPAGEAPP_NO_DEPRECATED
#    define KOPAGEAPP_NO_DEPRECATED
#  endif
#endif

#endif /* KOPAGEAPP_EXPORT_H */
