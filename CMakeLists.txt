cmake_minimum_required(VERSION 3.24)
project(sdl-wrap-dev)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin-int)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin-int)

option(BUILD_DEMO "Build the demo" OFF)

if(BUILD_DEMO)
    set(SDL3MIXER_CMD OFF)
    set(SDL3MIXER_FLAC OFF)
    set(SDL3MIXER_SNDFILE OFF)
    set(SDL3MIXER_GME OFF)
    set(SDL3MIXER_MOD OFF)
    set(SDL3MIXER_MIDI OFF)
    set(SDL3MIXER_MP3 OFF)
    set(SDL3MIXER_OPUS OFF)
    set(SDL3MIXER_VORBIS OFF)
    set(SDL3MIXER_WAVE OFF)
    set(SDL3MIXER_WAVPACK OFF)
endif()


add_subdirectory(Library)

if(BUILD_DEMO)
    add_subdirectory(Demo)
endif()