
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

if(${GENERATE_GREETINGS_SHARED_LIBRARY})
   add_definitions(-DGENERATE_GREETINGS_SHARED_LIBRARY)
   add_library(greetings SHARED ${source_files} ${include_files})
else(${GENERATE_GREETINGS_SHARED_LIBRARY})
   add_library(greetings STATIC  ${source_files} ${include_files})
endif(${GENERATE_GREETINGS_SHARED_LIBRARY})

