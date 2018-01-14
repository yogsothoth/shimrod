cmake_minimum_required(VERSION 3.10.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")

project(shimrod)

set(shimrod_VERSION "0.1.0")

enable_testing()

add_subdirectory(shimrod-cli)
add_subdirectory(libshimrod)
add_subdirectory(test)








