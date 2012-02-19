add_definitions(-DTESTS_EXPORTS)

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

add_library(greetings SHARED ${source_files} ${include_files})

