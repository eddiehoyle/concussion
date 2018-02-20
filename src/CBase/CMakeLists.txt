get_filename_component(DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
set(TARGET_NAME ${DIR_NAME})
set(TARGET_SOURCE_DIR defs)

file(GLOB PROJECT_SOURCES ${TARGET_SOURCE_DIR}/log.cc)
file(GLOB PROJECT_HEADERS log.hh)
file(GLOB PROJECT_CONFIGS CMakeLists.txt)

add_library(${TARGET_NAME} SHARED
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS} defs/assert.cc assert.hh)
target_compile_definitions(${TARGET_NAME} PRIVATE
        -DCNC_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}"
        -DCNC_TARGET_NAME="${TARGET_NAME}")
target_link_libraries(${TARGET_NAME}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        glfw)


