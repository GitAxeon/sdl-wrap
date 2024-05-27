cmake_minimum_required(VERSION 3.24)
project(wrapper VERSION 0.0.1 DESCRIPTION "A wrapper over SDL3")

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(vendor/SDL)
add_subdirectory(vendor/SDL_mixer)

file(
    GLOB_RECURSE source-files
    "src/*.cpp"
)
    
add_library(sdlW STATIC ${source-files})

target_include_directories(sdlW
    PUBLIC
    "include/"
    "vendor/SDL/include/"
    "vendor/SDL_mixer/include"
    "vendor/STB/"
)

target_link_libraries(
    sdlW PUBLIC
    SDL3::SDL3
    SDL3_mixer::SDL3_mixer
)