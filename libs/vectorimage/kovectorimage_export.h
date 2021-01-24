
#ifndef KOVECTORIMAGE_EXPORT_H
#define KOVECTORIMAGE_EXPORT_H

#ifdef KOVECTORIMAGE_STATIC_DEFINE
#  define KOVECTORIMAGE_EXPORT
#  define KOVECTORIMAGE_NO_EXPORT
#else
#  ifndef KOVECTORIMAGE_EXPORT
#    ifdef kovectorimage_EXPORTS
        /* We are building this library */
#      define KOVECTORIMAGE_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define KOVECTORIMAGE_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef KOVECTORIMAGE_NO_EXPORT
#    define KOVECTORIMAGE_NO_EXPORT 
#  endif
#endif

#ifndef KOVECTORIMAGE_DEPRECATED
#  define KOVECTORIMAGE_DEPRECATED __declspec(deprecated)
#endif

#ifndef KOVECTORIMAGE_DEPRECATED_EXPORT
#  define KOVECTORIMAGE_DEPRECATED_EXPORT KOVECTORIMAGE_EXPORT KOVECTORIMAGE_DEPRECATED
#endif

#ifndef KOVECTORIMAGE_DEPRECATED_NO_EXPORT
#  define KOVECTORIMAGE_DEPRECATED_NO_EXPORT KOVECTORIMAGE_NO_EXPORT KOVECTORIMAGE_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef KOVECTORIMAGE_NO_DEPRECATED
#    define KOVECTORIMAGE_NO_DEPRECATED
#  endif
#endif

#endif /* KOVECTORIMAGE_EXPORT_H */