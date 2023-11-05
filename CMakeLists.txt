cmake_minimum_required(VERSION 3.24)
project(sdl-wrap-dev)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin-int)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin-int)

option(BUILD_DEMO "Build the demo" OFF)

add_subdirectory(Library)

if(BUILD_DEMO)
    add_subdirectory(Demo)
endif()