# CMake is in parent scope here, make source file path absolute
set(TEST_ABSTRACTEVENT_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/testAbstractEvent.cc PARENT_SCOPE)
set(TEST_EVENT_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/testEvent.cc PARENT_SCOPE)
