
#ifndef KOWIDGETS_EXPORT_H
#define KOWIDGETS_EXPORT_H

#ifdef KOWIDGETS_STATIC_DEFINE
#  define KOWIDGETS_EXPORT
#  define KOWIDGETS_NO_EXPORT
#else
#  ifndef KOWIDGETS_EXPORT
#    ifdef kowidgets_EXPORTS
        /* We are building this library */
#      define KOWIDGETS_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define KOWIDGETS_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef KOWIDGETS_NO_EXPORT
#    define KOWIDGETS_NO_EXPORT 
#  endif
#endif

#ifndef KOWIDGETS_DEPRECATED
#  define KOWIDGETS_DEPRECATED __declspec(deprecated)
#endif

#ifndef KOWIDGETS_DEPRECATED_EXPORT
#  define KOWIDGETS_DEPRECATED_EXPORT KOWIDGETS_EXPORT KOWIDGETS_DEPRECATED
#endif

#ifndef KOWIDGETS_DEPRECATED_NO_EXPORT
#  define KOWIDGETS_DEPRECATED_NO_EXPORT KOWIDGETS_NO_EXPORT KOWIDGETS_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef KOWIDGETS_NO_DEPRECATED
#    define KOWIDGETS_NO_DEPRECATED
#  endif
#endif

#endif /* KOWIDGETS_EXPORT_H */
