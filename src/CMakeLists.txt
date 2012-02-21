add_subdirectory(downstream)
add_subdirectory(main)
add_subdirectory(sqlite)
add_subdirectory(transaction)

if(${GENERATE_HELLO_EXAMPLE})
   add_subdirectory(greetings)
endif(${GENERATE_HELLO_EXAMPLE})
