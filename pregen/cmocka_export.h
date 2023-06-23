#ifndef CMOCKA_EXPORT_H
#define CMOCKA_EXPORT_H

#ifdef CMOCKA_STATIC_DEFINE
#  define CMOCKA_EXPORT
#  define CMOCKA_NO_EXPORT
#else
#  ifndef CMOCKA_EXPORT
#    ifdef CMOCKA_EXPORTS
        /* We are building this library */
#if defined(_MSC_VER) || defined(__MINGW32__) || defined(__MSYS__) || defined(__CYGWIN__)
#      define CMOCKA_EXPORT __declspec(dllexport)
#elif defined(__SUNPRO_C)
#      define CMOCKA_EXPORT __global
#else
#      define CMOCKA_EXPORT __attribute__((visibility("default")))
#endif /* defined(_MSC_VER) || defined(__MINGW32__) || defined(__MSYS__) || defined(__CYGWIN__) */
#    else
        /* We are using this library */
#if defined(_MSC_VER) || defined(__MINGW32__) || defined(__MSYS__) || defined(__CYGWIN__)
#      define CMOCKA_EXPORT __declspec(dllimport)
#elif defined(__SUNPRO_C)
#      define CMOCKA_EXPORT __global
#else
#      define CMOCKA_EXPORT __attribute__((visibility("default")))
#endif /* defined(_MSC_VER) || defined(__MINGW32__) || defined(__MSYS__) || defined(__CYGWIN__) */
#    endif /* CMOCKA_EXPORTS */
#  endif /* ! CMOCKA_EXPORT */

#  ifndef CMOCKA_NO_EXPORT
#if defined(_MSC_VER) || defined(__MINGW32__) || defined(__MSYS__) || defined(__CYGWIN__) || defined(__SUNPRO_C)
#    define CMOCKA_NO_EXPORT
#else
#    define CMOCKA_NO_EXPORT __attribute__((visibility("hidden")))
#endif /* defined(_MSC_VER) || defined(__MINGW32__) || defined(__MSYS__) || defined(__CYGWIN__) || defined(__SUNPRO_C) */
#endif /* ! CMOCKA_NO_EXPORT */
#endif /* CMOCKA_STATIC_DEFINE */

#ifndef CMOCKA_DEPRECATED
#if defined(_MSC_VER) || defined(__MINGW32__) || defined(__MSYS__) || defined(__CYGWIN__)
#  define CMOCKA_DEPRECATED __declspec(deprecated)
#elif defined(__SUNPRO_C)
#  define CMOCKA_DEPRECATED
#else
#  define CMOCKA_DEPRECATED __attribute__ ((__deprecated__))
#endif /* defined(_MSC_VER) || defined(__MINGW32__) || defined(__MSYS__) || defined(__CYGWIN__) */
#endif /* ! CMOCKA_DEPRECATED */

#ifndef CMOCKA_DEPRECATED_EXPORT
#  define CMOCKA_DEPRECATED_EXPORT CMOCKA_EXPORT CMOCKA_DEPRECATED
#endif /* ! CMOCKA_DEPRECATED_EXPORT */

#ifndef CMOCKA_DEPRECATED_NO_EXPORT
#  define CMOCKA_DEPRECATED_NO_EXPORT CMOCKA_NO_EXPORT CMOCKA_DEPRECATED
#endif /* ! CMOCKA_DEPRECATED_NO_EXPORT */

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef CMOCKA_NO_DEPRECATED
#    define CMOCKA_NO_DEPRECATED
#  endif /* ! CMOCKA_NO_DEPRECATED */
#endif /* 0 */

#endif /* !CMOCKA_EXPORT_H */
