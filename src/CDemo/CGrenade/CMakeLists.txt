get_filename_component(DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
set(TARGET_NAME CDemoGrenade)
set(TARGET_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(TARGET_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_VERBOSE_MAKEFILE ON)

file(GLOB PROJECT_SOURCES ${TARGET_SOURCE_DIR}/*.cc)
file(GLOB PROJECT_HEADERS ${TARGET_INCLUDE_DIR}/*.hh)
file(GLOB PROJECT_CONFIGS CMakeLists.txt)

add_executable(${TARGET_NAME}
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS})
target_include_directories(${TARGET_NAME} PRIVATE
        ${TARGET_INCLUDE_DIR})
target_compile_definitions(${TARGET_NAME} PUBLIC
        -DCNC_TARGET_NAME="${TARGET_NAME}")
target_link_libraries(${TARGET_NAME}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        glfw
        CEngine
        tinyobjloader)



