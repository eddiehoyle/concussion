cmake_minimum_required(VERSION 3.5)
project(concussion)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CNC_LOGGING_ENABLED true)
set(CNC_ASSERT_ENABLED true)

set(CNC_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(CNC_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(CNC_EXTERNAL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ext)
set(CNC_RESOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/res)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(
        ${GLEW_INCLUDE_DIR}
        ext/glfw/include
        ext/glm
        ext/stb
        ext/tinyobjloader
        ext/googletest
        ${CNC_INCLUDE_DIR})

add_definitions(
        -DCNC_LOGGING_ENABLED=${CNC_LOGGING_ENABLED}
        -DCNC_ASSERT_ENABLED=${CNC_ASSERT_ENABLED}
        -DCNC_SOURCE_DIR="${CNC_SOURCE_DIR}"
        -DCNC_RESOURCES_DIR="${CNC_RESOURCE_DIR}"
)

add_subdirectory(${CNC_EXTERNAL_DIR})
add_subdirectory(${CNC_SOURCE_DIR})