cmake_minimum_required(VERSION 3.20)

project(igi-made-in-china)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(app
    src/main.cpp
    src/application.cpp
    src/game.cpp
    src/window.cpp
    src/renderer.cpp
    src/log.cpp
    src/utils.cpp
    external/glad/src/glad.c
)

target_include_directories(app PRIVATE
    src
    external/glad/include
    ${CMAKE_SOURCE_DIR}/vcpkg_installed/x64-linux/include
)


find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(Freetype REQUIRED)

target_link_libraries(app PRIVATE
    glfw
    OpenGL::GL
    Freetype::Freetype
)

if(WIN32)
    target_link_libraries(app PRIVATE dwmapi)
endif()


target_compile_definitions(app PRIVATE DEBUG)

