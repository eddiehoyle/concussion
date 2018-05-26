include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

add_executable(test_CEngine testMain.cc testEntity.cc)
target_link_libraries(test_CEngine CEngine gtest gtest_main)
