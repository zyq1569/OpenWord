
#ifndef PIGMENTCMS_EXPORT_H
#define PIGMENTCMS_EXPORT_H

#ifdef PIGMENT_STATIC_DEFINE
#  define PIGMENTCMS_EXPORT
#  define PIGMENT_NO_EXPORT
#else
#  ifndef PIGMENTCMS_EXPORT
#    ifdef pigmentcms_EXPORTS
        /* We are building this library */
#      define PIGMENTCMS_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define PIGMENTCMS_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef PIGMENT_NO_EXPORT
#    define PIGMENT_NO_EXPORT 
#  endif
#endif

#ifndef PIGMENT_DEPRECATED
#  define PIGMENT_DEPRECATED __declspec(deprecated)
#endif

#ifndef PIGMENT_DEPRECATED_EXPORT
#  define PIGMENT_DEPRECATED_EXPORT PIGMENTCMS_EXPORT PIGMENT_DEPRECATED
#endif

#ifndef PIGMENT_DEPRECATED_NO_EXPORT
#  define PIGMENT_DEPRECATED_NO_EXPORT PIGMENT_NO_EXPORT PIGMENT_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef PIGMENT_NO_DEPRECATED
#    define PIGMENT_NO_DEPRECATED
#  endif
#endif

#endif /* PIGMENTCMS_EXPORT_H */
