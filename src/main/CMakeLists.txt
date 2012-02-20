add_executable(hello hello.cpp)
target_link_libraries(hello greetings)

add_subdirectory(tests)

