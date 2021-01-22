
#ifndef WORDS_EXPORT_H
#define WORDS_EXPORT_H

#ifdef WORDS_STATIC_DEFINE
#  define WORDS_EXPORT
#  define WORDS_NO_EXPORT
#else
#  ifndef WORDS_EXPORT
#    ifdef wordsprivate_EXPORTS
        /* We are building this library */
#      define WORDS_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define WORDS_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef WORDS_NO_EXPORT
#    define WORDS_NO_EXPORT 
#  endif
#endif

#ifndef WORDS_DEPRECATED
#  define WORDS_DEPRECATED __declspec(deprecated)
#endif

#ifndef WORDS_DEPRECATED_EXPORT
#  define WORDS_DEPRECATED_EXPORT WORDS_EXPORT WORDS_DEPRECATED
#endif

#ifndef WORDS_DEPRECATED_NO_EXPORT
#  define WORDS_DEPRECATED_NO_EXPORT WORDS_NO_EXPORT WORDS_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef WORDS_NO_DEPRECATED
#    define WORDS_NO_DEPRECATED
#  endif
#endif

#endif /* WORDS_EXPORT_H */
