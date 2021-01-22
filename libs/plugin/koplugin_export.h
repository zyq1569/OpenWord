
#ifndef KOPLUGIN_EXPORT_H
#define KOPLUGIN_EXPORT_H

#ifdef KOPLUGIN_STATIC_DEFINE
#  define KOPLUGIN_EXPORT
#  define KOPLUGIN_NO_EXPORT
#else
#  ifndef KOPLUGIN_EXPORT
#    ifdef koplugin_EXPORTS
        /* We are building this library */
#      define KOPLUGIN_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define KOPLUGIN_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef KOPLUGIN_NO_EXPORT
#    define KOPLUGIN_NO_EXPORT 
#  endif
#endif

#ifndef KOPLUGIN_DEPRECATED
#  define KOPLUGIN_DEPRECATED __declspec(deprecated)
#endif

#ifndef KOPLUGIN_DEPRECATED_EXPORT
#  define KOPLUGIN_DEPRECATED_EXPORT KOPLUGIN_EXPORT KOPLUGIN_DEPRECATED
#endif

#ifndef KOPLUGIN_DEPRECATED_NO_EXPORT
#  define KOPLUGIN_DEPRECATED_NO_EXPORT KOPLUGIN_NO_EXPORT KOPLUGIN_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef KOPLUGIN_NO_DEPRECATED
#    define KOPLUGIN_NO_DEPRECATED
#  endif
#endif

#endif /* KOPLUGIN_EXPORT_H */
