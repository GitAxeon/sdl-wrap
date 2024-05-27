cmake_minimum_required(VERSION 3.24)
project(sdl-wrap-demo)

set(CMAKE_CXX_STANDARD 20)

file(
    GLOB_RECURSE source-files
    "src/*.cpp"
)

add_executable(wrap-demo ${source-files})

target_link_libraries(wrap-demo PRIVATE sdlW)

set(resources-dir ${CMAKE_CURRENT_SOURCE_DIR}/resources/)
set(destination-dir ${RUNTIME_OUTPUT_DIRECTORY}/resources)

add_custom_target(copy_resources
    COMMAND ${CMAKE_COMMAND} -E make_directory ${destination-dir}
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${resources-dir} $<TARGET_FILE_DIR:wrap-demo>/resources
    COMMENT "Copying resources to build directory"
)