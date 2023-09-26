cmake_minimum_required(VERSION 3.24)
project(sdl-wrap)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin-int)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin-int)

file(
    GLOB_RECURSE source-files
    "src/*.cpp"
    "src/*.hpp"
)

add_executable(sdl-wrap)


target_include_directories(
    sdl-wrap PRIVATE
    vendor/SDL/include/
)

target_link_libraries(
    sdl-wrap PRIVATE
    SDL3::SDL3
)