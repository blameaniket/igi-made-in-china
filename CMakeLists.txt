cmake_minimum_required(VERSION 3.20)

project(igi-made-in-china LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(app
    src/main.cpp
    src/game.cpp
    src/window.cpp
    external/glad/src/glad.c
)

find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(Freetype REQUIRED)

target_include_directories(app PRIVATE
    src
    external/glad/include
)

target_link_libraries(app PRIVATE
    glfw
    OpenGL::GL
    Freetype::Freetype
)

target_compile_definitions(app PRIVATE DEBUG)

# Format source files with clang-format.
find_program(CLANG_FORMAT clang-format REQUIRED)

set(FORMAT_SOURCES
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/game.cpp
    ${CMAKE_SOURCE_DIR}/src/window.cpp
)

add_custom_target(format
    COMMAND ${CLANG_FORMAT} -i ${FORMAT_SOURCES}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Formatting source files with clang-format"
)
