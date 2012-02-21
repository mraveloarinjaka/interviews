if(CYGWIN OR MINGW)
   add_definitions(-DSQLITE_WIN32_MALLOC)
   message("-- Platform: cygwin or mingw.")
endif()


set(SQLITE_INCLUDE_DIRECTORY ${CMAKE_SOURCE_DIR}/include/sqlite)

file (
   GLOB_RECURSE
   include_files
   ${SQLITE_INCLUDE_DIRECTORY}/*.h	
)

if(UNIX)
find_package(Threads)
add_library(sqlite STATIC sqlite3.c)
target_link_libraries(sqlite dl ${CMAKE_THREAD_LIBS_INIT})
else(UNIX)
add_library(sqlite STATIC sqlite3.c)
target_link_libraries(sqlite)
endif(UNIX)

include_directories(${SQLITE_INCLUDE_DIRECTORY})
add_executable(sqlite_shell shell.c ${include_files})
target_link_libraries(sqlite_shell sqlite)

