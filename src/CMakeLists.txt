#CMakeLists file for server

set(HDRS 
      )
 
set(SRCS
      main.cpp
)
 
add_executable(PixelPacker ${HDRS} ${SRCS})
target_link_libraries(PixelPacker PixelGui PixelPak PixelCli PixelUtil ${Boost_LIBRARIES} ${MAGICK++_LIBRARIES}  JsonCpp)

include_directories(util)

add_subdirectory(gui)
add_subdirectory(pak)
add_subdirectory(cli)
add_subdirectory(util)
