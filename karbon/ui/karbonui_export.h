
#ifndef KARBONUI_EXPORT_H
#define KARBONUI_EXPORT_H

#ifdef KARBONUI_STATIC_DEFINE
#  define KARBONUI_EXPORT
#  define KARBONUI_NO_EXPORT
#else
#  ifndef KARBONUI_EXPORT
#    ifdef karbonui_EXPORTS
        /* We are building this library */
#      define KARBONUI_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define KARBONUI_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef KARBONUI_NO_EXPORT
#    define KARBONUI_NO_EXPORT 
#  endif
#endif

#ifndef KARBONUI_DEPRECATED
#  define KARBONUI_DEPRECATED __declspec(deprecated)
#endif

#ifndef KARBONUI_DEPRECATED_EXPORT
#  define KARBONUI_DEPRECATED_EXPORT KARBONUI_EXPORT KARBONUI_DEPRECATED
#endif

#ifndef KARBONUI_DEPRECATED_NO_EXPORT
#  define KARBONUI_DEPRECATED_NO_EXPORT KARBONUI_NO_EXPORT KARBONUI_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef KARBONUI_NO_DEPRECATED
#    define KARBONUI_NO_DEPRECATED
#  endif
#endif

#endif /* KARBONUI_EXPORT_H */
