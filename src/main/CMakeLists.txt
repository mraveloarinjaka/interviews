add_executable(main main.cpp)
target_link_libraries(main sqlite transaction)

if(${GENERATE_HELLO_EXAMPLE})
   if(${GENERATE_GREETINGS_SHARED_LIBRARY})
      add_definitions(-DGENERATE_GREETINGS_SHARED_LIBRARY)
   endif(${GENERATE_GREETINGS_SHARED_LIBRARY})
   add_executable(hello hello.cpp)
   target_link_libraries(hello greetings)
endif(${GENERATE_HELLO_EXAMPLE})

add_subdirectory(tests)

