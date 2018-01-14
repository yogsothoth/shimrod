cmake_minimum_required(VERSION 3.10.1)

set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/catch)
include_directories(${CMAKE_SOURCE_DIR}/libshimrod/include)

add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

set(TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/TestViewport.cc)

add_executable(shimrod_test
	${TEST_SOURCES})

target_link_libraries(shimrod_test libshimrod Catch)

add_test(NAME ShimrodTest COMMAND shimrod_test)
