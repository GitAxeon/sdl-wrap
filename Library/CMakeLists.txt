cmake_minimum_required(VERSION 3.24)
project(wrapper VERSION 0.0.1 DESCRIPTION "A wrapper over SDL3")

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(vendor/SDL)

file(
    GLOB_RECURSE source-files
    "src/*.cpp"
)
    
add_library(sdlW SHARED ${source-files})
add_compile_definitions(MExport)

target_include_directories(
    sdlW PUBLIC
    "vendor/SDL/include/"
    "vendor/STB/"
    "include/"
    "src/"
)

target_link_libraries(
    sdlW PUBLIC
    SDL3::SDL3
)