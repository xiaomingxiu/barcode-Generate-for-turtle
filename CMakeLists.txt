project(dmcreator)
cmake_minimum_required (VERSION 2.8)
find_package( OpenCV REQUIRED )
include_directories(${OpenCV_INCLUDE_DIRS} )
message(where ${OpenCV_INCLUDE_DIRS} )
SET(SRC_lIST main.cpp)
#SET( CMAKE_VERBOSE_MAKEFILE on )
#include_directories(/usr/local/lib)
#include_directories(/usr/local/include)
add_executable( dmcreator ${SRC_lIST})
target_link_libraries(dmcreator  ${OpenCV_LIBS}  libdmtx.so)


