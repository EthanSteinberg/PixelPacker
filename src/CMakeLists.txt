#CMakeLists file for server

cmake_minimum_required(VERSION 2.6)

set(CMAKE_BUILD_TYPE Debug)

#set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -Wshadow")
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -march=native -O2")

set(HDRS 
      )
 
set(SRCS
      main.cpp
)
 
add_executable(App ${HDRS} ${SRCS})

