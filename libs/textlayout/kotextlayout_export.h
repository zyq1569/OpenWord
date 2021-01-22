
#ifndef KOTEXTLAYOUT_EXPORT_H
#define KOTEXTLAYOUT_EXPORT_H

#ifdef KOTEXTLAYOUT_STATIC_DEFINE
#  define KOTEXTLAYOUT_EXPORT
#  define KOTEXTLAYOUT_NO_EXPORT
#else
#  ifndef KOTEXTLAYOUT_EXPORT
#    ifdef kotextlayout_EXPORTS
        /* We are building this library */
#      define KOTEXTLAYOUT_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define KOTEXTLAYOUT_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef KOTEXTLAYOUT_NO_EXPORT
#    define KOTEXTLAYOUT_NO_EXPORT 
#  endif
#endif

#ifndef KOTEXTLAYOUT_DEPRECATED
#  define KOTEXTLAYOUT_DEPRECATED __declspec(deprecated)
#endif

#ifndef KOTEXTLAYOUT_DEPRECATED_EXPORT
#  define KOTEXTLAYOUT_DEPRECATED_EXPORT KOTEXTLAYOUT_EXPORT KOTEXTLAYOUT_DEPRECATED
#endif

#ifndef KOTEXTLAYOUT_DEPRECATED_NO_EXPORT
#  define KOTEXTLAYOUT_DEPRECATED_NO_EXPORT KOTEXTLAYOUT_NO_EXPORT KOTEXTLAYOUT_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef KOTEXTLAYOUT_NO_DEPRECATED
#    define KOTEXTLAYOUT_NO_DEPRECATED
#  endif
#endif

#endif /* KOTEXTLAYOUT_EXPORT_H */
