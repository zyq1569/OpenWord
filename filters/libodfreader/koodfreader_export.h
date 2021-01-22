
#ifndef KOODFREADER_EXPORT_H
#define KOODFREADER_EXPORT_H

#ifdef KOODFREADER_STATIC_DEFINE
#  define KOODFREADER_EXPORT
#  define KOODFREADER_NO_EXPORT
#else
#  ifndef KOODFREADER_EXPORT
#    ifdef koodfreader_EXPORTS
        /* We are building this library */
#      define KOODFREADER_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define KOODFREADER_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef KOODFREADER_NO_EXPORT
#    define KOODFREADER_NO_EXPORT 
#  endif
#endif

#ifndef KOODFREADER_DEPRECATED
#  define KOODFREADER_DEPRECATED __declspec(deprecated)
#endif

#ifndef KOODFREADER_DEPRECATED_EXPORT
#  define KOODFREADER_DEPRECATED_EXPORT KOODFREADER_EXPORT KOODFREADER_DEPRECATED
#endif

#ifndef KOODFREADER_DEPRECATED_NO_EXPORT
#  define KOODFREADER_DEPRECATED_NO_EXPORT KOODFREADER_NO_EXPORT KOODFREADER_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef KOODFREADER_NO_DEPRECATED
#    define KOODFREADER_NO_DEPRECATED
#  endif
#endif

#endif /* KOODFREADER_EXPORT_H */
