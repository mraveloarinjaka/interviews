cmake_minimum_required(VERSION 2.8)

project(murex_tests) 
 
# Projects includes
include_directories(./include)

# Projects outputs
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_subdirectory(src)
 
