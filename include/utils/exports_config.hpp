#ifndef TESTS_CONFIG_HPP
#define TESTS_CONFIG_HPP

#if !defined(TESTS_DECLSPEC) && defined(_MSC_VER)
# define TESTS_DECLSPEC
#endif

// Windows DLL suport
#ifdef TESTS_DECLSPEC
// export if this is our own source, otherwise import:
#ifdef TESTS_EXPORTS
# define TESTS_API __declspec(dllexport)
#else
# define TESTS_API __declspec(dllimport)
#endif  // TESTS_EXPORTS
#endif  // TESTS_DECLSPEC

#ifndef TESTS_API
# define TESTS_API 
#endif

#endif  // TESTS_CONFIG_HPP
