cmake_minimum_required(VERSION 3.9)
project(tAItris C)

set(CMAKE_VERBOSE_MAKEFILE OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -std=c99 -O0 -g3")
add_definitions(-D_XOPEN_SOURCE=500)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
link_directories(${SDL2_LIBRARY_DIRS})

file(GLOB_RECURSE source_files src/*)
add_executable(tAItris ${source_files})

target_link_libraries(tAItris ${SDL2_LIBRARIES})

add_custom_command(TARGET tAItris PRE_BUILD
        COMMAND rsync -rup --delete ${CMAKE_HOME_DIRECTORY}/res ${CMAKE_HOME_DIRECTORY}/bin
        DEPENDS always_rebuild)

add_custom_command(TARGET tAItris PRE_BUILD
        COMMAND rsync -rup --delete ${CMAKE_HOME_DIRECTORY}/data ${CMAKE_HOME_DIRECTORY}/bin
        DEPENDS always_rebuild)