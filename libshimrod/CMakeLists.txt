cmake_minimum_required(VERSION 3.10.1)

set(CMAKE_CXX_STANDARD 14)

set(libshimrod_SRCS  ${CMAKE_CURRENT_SOURCE_DIR}/src/Viewport.cc
		     ${CMAKE_CURRENT_SOURCE_DIR}/src/Image.cc
		     ${CMAKE_CURRENT_SOURCE_DIR}/src/Fractals.cc)
	
include_directories("/usr/local/include/ImageMagick-6/"
		    ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_definitions(-DMAGICKCORE_HDRI_ENABLE=0
		-DMAGICKCORE_QUANTUM_DEPTH=16)

add_library(libshimrod STATIC ${libshimrod_SRCS})

target_include_directories(libshimrod PUBLIC
			   ${CMAKE_CURRENT_SOURCE_DIR})






