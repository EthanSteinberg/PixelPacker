cmake_minimum_required(VERSION 2.6)

project(Base)

if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
   message(FATAL_ERROR "ERROR: Building in source, please build out of it")
endif()

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -march=k8 -std=c++0x   -O2 -Wshadow  -lpthread")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")	

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/arch)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(Boost_ADDITIONAL_VERSIONS "1.42" "1.42.0" "1.41.0" "1.41" "1.40.0" "1.40" "1.39.0" "1.39" "1.38.0" "1.38" "1.37.0" "1.37" )
set(BOOST_COMPONENTS system thread date_time program_options filesystem)

find_package(Boost COMPONENTS ${BOOST_COMPONENTS} REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

find_package(Magick REQUIRED)
include_directories(${MAGICK++_INCLUDE_DIR})

find_package(GTK2 REQUIRED gtk gtkmm) 
include_directories(${GTK2_INCLUDE_DIRS} /usr/include/freetype2)

#Bad way of doing jsoncpp, I know
#link_directories(${CMAKE_SOURCE_DIR}/lib/jsoncpp-src-0.5.0/libs/linux-gcc-4.4.5)
add_library(JsonCpp STATIC IMPORTED)
set_property(TARGET JsonCpp PROPERTY IMPORTED_LOCATION 
${CMAKE_SOURCE_DIR}/lib/jsoncpp-src-0.5.0/libs/linux-gcc-4.4.5/libjson_linux-gcc-4.4.5_libmt.a)

include_directories(lib/jsoncpp-src-0.5.0/include)

add_subdirectory(src) 

