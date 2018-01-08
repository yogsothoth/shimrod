cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 14)

project(shimrod)

set(shimrod_VERSION "0.1.0")
set(shimrod_SRCS  src/Viewport.cc
		  src/Image.cc
		  src/Fractals.cc
		  src/main.cc)
		    

include_directories("/usr/local/include/ImageMagick-6/")
link_directories("/usr/local/lib/")
add_definitions(-DMAGICKCORE_HDRI_ENABLE=0 -DMAGICKCORE_QUANTUM_DEPTH=16)

add_executable(shimrod ${shimrod_SRCS})

#find_package(ImageMagick REQUIRED)
#include_directories(${ImageMagick_INCLUDE_DIR} "/usr/local/include/ImageMagick-6/")
#target_link_libraries(shimrod ${ImageMagick_LIBRARIES} Magick++-6 MagickWand-6 MagickCore-6)

target_link_libraries(shimrod Magick++-6 MagickWand-6 MagickCore-6)






