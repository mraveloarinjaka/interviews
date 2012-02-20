if(${GENERATE_GREETINGS_SHARED_LIBRARY})
   add_definitions(-DGENERATE_GREETINGS_SHARED_LIBRARY)
endif(${GENERATE_GREETINGS_SHARED_LIBRARY})

add_executable(hello hello.cpp)
target_link_libraries(hello greetings)

add_executable(main main.cpp)
target_link_libraries(main sqlite transaction)

add_subdirectory(tests)

