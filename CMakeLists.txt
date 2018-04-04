cmake_minimum_required(VERSION 3.9)
project(tAItris C)

set(CMAKE_VERBOSE_MAKEFILE OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -std=c99 -O0 -g3")
add_definitions(-D_XOPEN_SOURCE=500)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

file(GLOB_RECURSE source_files src/*)
add_executable(tAItris ${source_files})

target_link_libraries(tAItris ${GTK3_LIBRARIES})
target_link_libraries(tAItris m)

add_custom_command(TARGET tAItris PRE_BUILD
        COMMAND rsync -rup --delete ${CMAKE_HOME_DIRECTORY}/res ${CMAKE_HOME_DIRECTORY}/bin
        DEPENDS always_rebuild)

add_custom_command(TARGET tAItris PRE_BUILD
        COMMAND rsync -rup --delete ${CMAKE_HOME_DIRECTORY}/data ${CMAKE_HOME_DIRECTORY}/bin
        DEPENDS always_rebuild)