
#ifndef KOKROSS_EXPORT_H
#define KOKROSS_EXPORT_H

#ifdef KOKROSS_STATIC_DEFINE
#  define KOKROSS_EXPORT
#  define KOKROSS_NO_EXPORT
#else
#  ifndef KOKROSS_EXPORT
#    ifdef kokross_EXPORTS
        /* We are building this library */
#      define KOKROSS_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define KOKROSS_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef KOKROSS_NO_EXPORT
#    define KOKROSS_NO_EXPORT 
#  endif
#endif

#ifndef KOKROSS_DEPRECATED
#  define KOKROSS_DEPRECATED __declspec(deprecated)
#endif

#ifndef KOKROSS_DEPRECATED_EXPORT
#  define KOKROSS_DEPRECATED_EXPORT KOKROSS_EXPORT KOKROSS_DEPRECATED
#endif

#ifndef KOKROSS_DEPRECATED_NO_EXPORT
#  define KOKROSS_DEPRECATED_NO_EXPORT KOKROSS_NO_EXPORT KOKROSS_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef KOKROSS_NO_DEPRECATED
#    define KOKROSS_NO_DEPRECATED
#  endif
#endif

#endif /* KOKROSS_EXPORT_H */
