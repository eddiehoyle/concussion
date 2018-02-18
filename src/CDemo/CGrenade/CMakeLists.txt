set(CMAKE_VERBOSE_MAKEFILE ON)

get_filename_component(DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
set(TARGET_NAME demo${DIR_NAME})

file(GLOB PROJECT_SOURCES main.cc)
file(GLOB PROJECT_CONFIGS CMakeLists.txt)

message(WARNING ${LIB_CBASE})

add_executable(${TARGET_NAME} ${PROJECT_SOURCES})
target_compile_definitions(${TARGET_NAME} PRIVATE
        -DCNC_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
        -DCNC_DEMO_NAME="${TARGET_NAME}")
target_link_libraries(${TARGET_NAME}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        glfw
        CBase)
