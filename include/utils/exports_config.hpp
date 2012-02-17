#ifndef MUREX_TESTS_CONFIG_HPP
#define MUREX_TESTS_CONFIG_HPP

#if !defined(MUREX_TESTS_DECLSPEC) && defined(_MSC_VER)
# define MUREX_TESTS_DECLSPEC
#endif

// Windows DLL suport
#ifdef MUREX_TESTS_DECLSPEC
// export if this is our own source, otherwise import:
#ifdef MUREX_TESTS_EXPORTS
# define MUREX_TESTS_API __declspec(dllexport)
#else
# define MUREX_TESTS_API __declspec(dllimport)
#endif  // MUREX_TESTS_EXPORTS
#endif  // MUREX_TESTS_DECLSPEC

#ifndef MUREX_TESTS_API
# define MUREX_TESTS_API 
#endif

#endif  // MUREX_TESTS_CONFIG_HPP
