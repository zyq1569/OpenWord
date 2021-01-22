
#ifndef RTFREADER_EXPORT_H
#define RTFREADER_EXPORT_H

#ifdef RTFREADER_STATIC_DEFINE
#  define RTFREADER_EXPORT
#  define RTFREADER_NO_EXPORT
#else
#  ifndef RTFREADER_EXPORT
#    ifdef RtfReader_EXPORTS
        /* We are building this library */
#      define RTFREADER_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define RTFREADER_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef RTFREADER_NO_EXPORT
#    define RTFREADER_NO_EXPORT 
#  endif
#endif

#ifndef RTFREADER_DEPRECATED
#  define RTFREADER_DEPRECATED __declspec(deprecated)
#endif

#ifndef RTFREADER_DEPRECATED_EXPORT
#  define RTFREADER_DEPRECATED_EXPORT RTFREADER_EXPORT RTFREADER_DEPRECATED
#endif

#ifndef RTFREADER_DEPRECATED_NO_EXPORT
#  define RTFREADER_DEPRECATED_NO_EXPORT RTFREADER_NO_EXPORT RTFREADER_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef RTFREADER_NO_DEPRECATED
#    define RTFREADER_NO_DEPRECATED
#  endif
#endif

#endif /* RTFREADER_EXPORT_H */
