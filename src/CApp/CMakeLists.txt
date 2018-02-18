set(TARGET_NAME concussion)

file(GLOB PROJECT_SOURCES main.cc)
file(GLOB PROJECT_CONFIGS CMakeLists.txt)

add_executable(${TARGET_NAME} ${PROJECT_SOURCES})
target_compile_definitions(${TARGET_NAME} PRIVATE
        -DSOURCE_DIR="")
target_link_libraries(${TARGET_NAME}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        glfw)
