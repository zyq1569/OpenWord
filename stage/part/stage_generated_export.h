
#ifndef STAGE_EXPORT_H
#define STAGE_EXPORT_H

#ifdef STAGE_STATIC_DEFINE
#  define STAGE_EXPORT
#  define STAGE_NO_EXPORT
#else
#  ifndef STAGE_EXPORT
#    ifdef calligrastageprivate_EXPORTS
        /* We are building this library */
#      define STAGE_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define STAGE_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef STAGE_NO_EXPORT
#    define STAGE_NO_EXPORT 
#  endif
#endif

#ifndef STAGE_DEPRECATED
#  define STAGE_DEPRECATED __declspec(deprecated)
#endif

#ifndef STAGE_DEPRECATED_EXPORT
#  define STAGE_DEPRECATED_EXPORT STAGE_EXPORT STAGE_DEPRECATED
#endif

#ifndef STAGE_DEPRECATED_NO_EXPORT
#  define STAGE_DEPRECATED_NO_EXPORT STAGE_NO_EXPORT STAGE_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef STAGE_NO_DEPRECATED
#    define STAGE_NO_DEPRECATED
#  endif
#endif

#endif /* STAGE_EXPORT_H */
