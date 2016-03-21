#CMakeLists file for server

set(HDRS 
      )
 
set(SRCS
      main.cpp
)
 
add_executable(PixelPacker ${HDRS} ${SRCS})
target_link_libraries(PixelPacker PixelPak PixelCli PixelUtil ${Boost_LIBRARIES} ${MAGICK++_LIBRARIES}  jsoncpp)

include_directories(util)

add_subdirectory(pak)
add_subdirectory(cli)
add_subdirectory(util)
