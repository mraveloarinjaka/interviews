file (
   GLOB_RECURSE
   source_files
   ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp	
)

file (
   GLOB_RECURSE
   include_files
   ${CMAKE_SOURCE_DIR}/include/transaction/*.hpp	
   ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp	
)

add_library(transaction STATIC ${source_files} ${include_files})

