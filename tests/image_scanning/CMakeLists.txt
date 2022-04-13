CMake_minimum_required(VERSION 2.8)
project( image_scanning )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( scanimg scanimg.cpp )
target_link_libraries( scanimg ${OpenCV_LIBS} )

