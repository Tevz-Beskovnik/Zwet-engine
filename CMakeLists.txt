cmake_minimum_required(VERSION 3.20.5)
project(Zwet_Engine VERSION 1.0)

include(${CMAKE_CURRENT_SOURCE_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_APPLE_SILICON_PROCESSOR arm64) # comment out for linux builds

file (GLOB_RECURSE Zwet_Engine_SOURCES CONFIGURE_DEPENDS "src/*.cpp")

add_executable("${CMAKE_PROJECT_NAME}" ${Zwet_Engine_SOURCES} "test/main.cpp")

target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC ZWET_DEBUG) # comment out for release build

target_link_libraries("${CMAKE_PROJECT_NAME}" CONAN_PKG::glfw CONAN_PKG::glew CONAN_PKG::openal CONAN_PKG::simdjson CONAN_PKG::tsl-hopscotch-map)

set(Zwet_Engine_HEADERS 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_include_directories("${CMAKE_PROJECT_NAME}"
    PUBLIC Zwet_Engine_HEADERS 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/core
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/debug
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/input
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/mesh
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/renderer
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/scene
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/utils
)