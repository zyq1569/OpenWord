
#ifndef WV2_EXPORT_H
#define WV2_EXPORT_H

#ifdef WV2_STATIC_DEFINE
#  define WV2_EXPORT
#  define WV2_NO_EXPORT
#else
#  ifndef WV2_EXPORT
#    ifdef kowv2_EXPORTS
        /* We are building this library */
#      define WV2_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define WV2_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef WV2_NO_EXPORT
#    define WV2_NO_EXPORT 
#  endif
#endif

#ifndef WV2_DEPRECATED
#  define WV2_DEPRECATED __declspec(deprecated)
#endif

#ifndef WV2_DEPRECATED_EXPORT
#  define WV2_DEPRECATED_EXPORT WV2_EXPORT WV2_DEPRECATED
#endif

#ifndef WV2_DEPRECATED_NO_EXPORT
#  define WV2_DEPRECATED_NO_EXPORT WV2_NO_EXPORT WV2_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef WV2_NO_DEPRECATED
#    define WV2_NO_DEPRECATED
#  endif
#endif

#endif /* WV2_EXPORT_H */
