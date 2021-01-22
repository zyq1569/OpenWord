
#ifndef KOMSOOXML_EXPORT_H
#define KOMSOOXML_EXPORT_H

#ifdef KOMSOOXML_STATIC_DEFINE
#  define KOMSOOXML_EXPORT
#  define KOMSOOXML_NO_EXPORT
#else
#  ifndef KOMSOOXML_EXPORT
#    ifdef komsooxml_EXPORTS
        /* We are building this library */
#      define KOMSOOXML_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define KOMSOOXML_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef KOMSOOXML_NO_EXPORT
#    define KOMSOOXML_NO_EXPORT 
#  endif
#endif

#ifndef KOMSOOXML_DEPRECATED
#  define KOMSOOXML_DEPRECATED __declspec(deprecated)
#endif

#ifndef KOMSOOXML_DEPRECATED_EXPORT
#  define KOMSOOXML_DEPRECATED_EXPORT KOMSOOXML_EXPORT KOMSOOXML_DEPRECATED
#endif

#ifndef KOMSOOXML_DEPRECATED_NO_EXPORT
#  define KOMSOOXML_DEPRECATED_NO_EXPORT KOMSOOXML_NO_EXPORT KOMSOOXML_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef KOMSOOXML_NO_DEPRECATED
#    define KOMSOOXML_NO_DEPRECATED
#  endif
#endif

#endif /* KOMSOOXML_EXPORT_H */
