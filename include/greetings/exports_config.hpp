#ifndef GREETINGS_EXPORT_CONFIG_HPP
#define GREETINGS_EXPORT_CONFIG_HPP

#if defined(GENERATE_GREETINGS_SHARED_LIBRARY) && !defined(GREETINGS_DECLSPEC) && defined(_MSC_VER)
# define GREETINGS_DECLSPEC
#endif

// Windows DLL suport
#ifdef GREETINGS_DECLSPEC
// export if this is our own source, otherwise import:
// the variable greetings_EXPORTS is defined by cmake when generating a shared library
#ifdef greetings_EXPORTS
# define TESTS_API __declspec(dllexport)
#else
# define TESTS_API __declspec(dllimport)
#endif  // greetings_EXPORTS
#endif  // GREETINGS_DECLSPEC

#ifndef TESTS_API
# define TESTS_API 
#endif

#endif  // GREETINGS_EXPORT_CONFIG_HPP

