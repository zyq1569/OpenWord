
#ifndef KARBONCOMMON_EXPORT_H
#define KARBONCOMMON_EXPORT_H

#ifdef KARBONCOMMON_STATIC_DEFINE
#  define KARBONCOMMON_EXPORT
#  define KARBONCOMMON_NO_EXPORT
#else
#  ifndef KARBONCOMMON_EXPORT
#    ifdef karboncommon_EXPORTS
        /* We are building this library */
#      define KARBONCOMMON_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define KARBONCOMMON_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef KARBONCOMMON_NO_EXPORT
#    define KARBONCOMMON_NO_EXPORT 
#  endif
#endif

#ifndef KARBONCOMMON_DEPRECATED
#  define KARBONCOMMON_DEPRECATED __declspec(deprecated)
#endif

#ifndef KARBONCOMMON_DEPRECATED_EXPORT
#  define KARBONCOMMON_DEPRECATED_EXPORT KARBONCOMMON_EXPORT KARBONCOMMON_DEPRECATED
#endif

#ifndef KARBONCOMMON_DEPRECATED_NO_EXPORT
#  define KARBONCOMMON_DEPRECATED_NO_EXPORT KARBONCOMMON_NO_EXPORT KARBONCOMMON_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef KARBONCOMMON_NO_DEPRECATED
#    define KARBONCOMMON_NO_DEPRECATED
#  endif
#endif

#endif /* KARBONCOMMON_EXPORT_H */
