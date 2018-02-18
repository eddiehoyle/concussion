cmake_minimum_required(VERSION 3.5)
project(concussion)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(LOGGING_ENABLED true)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(EXTERNAL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ext)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(
        ${GLEW_INCLUDE_DIR}
        ext/glfw/include
        ext/glm
        ext/stb
        ${INCLUDE_DIR})

add_subdirectory(${EXTERNAL_DIR})
add_subdirectory(${SOURCE_DIR})