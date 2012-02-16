file (
   GLOB_RECURSE
   source_files
   ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp	
)

file (
   GLOB_RECURSE
   include_files
   ${CMAKE_SOURCE_DIR}/include/greetings/*.hpp	
)

add_library(greetings STATIC ${source_files} ${include_files})

