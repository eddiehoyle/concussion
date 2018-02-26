get_filename_component(DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
set(TARGET_NAME ${DIR_NAME})
set(TARGET_SOURCE_DIR defs)
set(TARGET_INCLUDE_DIR .)

file(GLOB PROJECT_SOURCES ${TARGET_SOURCE_DIR}/**/*.cc)
file(GLOB PROJECT_HEADERS *.hh)
file(GLOB PROJECT_CONFIGS CMakeLists.txt)

add_library(${TARGET_NAME} SHARED
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS} defs/shader/manager.cc manager.hh defs/shader/domain.cc domain.hh)
target_include_directories(${TARGET_NAME} PRIVATE
        ${TARGET_INCLUDE_DIR})
target_compile_definitions(${TARGET_NAME} PRIVATE
        -DCNC_TARGET_NAME="${TARGET_NAME}")
target_link_libraries(${TARGET_NAME}
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        glfw
        CBase)



