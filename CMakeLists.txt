cmake_minimum_required(VERSION 2.6)

project(Base)

set(CMAKE_CXX_FLAGS "-Wall -std=c++14 -O2 -Wextra -Wno-unused-variable")

set(LIBRARY_FILES 
    lib/lodepng/lodepng.cpp
)

set(SOURCE_FILES 
    src/algoMaxRects.cpp
    src/main.cpp
    src/myBox.cpp
    src/myVector2.cpp
    src/algoMaxRects.cpp
    src/pixelPak.cpp
)

add_executable(PixelPacker ${SOURCE_FILES} ${LIBRARY_FILES})

include_directories(lib/json)
include_directories(lib/lodepng)

