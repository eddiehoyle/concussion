include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

enable_testing()

set(TEST_MAIN_SOURCE testMain.cc)
set(TEST_ENTITY_SOURCE testEntity.cc)

add_subdirectory(event)

add_executable(gtest_CEngine
        ${TEST_MAIN_SOURCE}
        ${TEST_ENTITY_SOURCE}
        ${TEST_ABSTRACTEVENT_SOURCE}
        ${TEST_EVENT_SOURCE})
target_link_libraries(gtest_CEngine
        gtest_main
        gtest
        CEngine)
