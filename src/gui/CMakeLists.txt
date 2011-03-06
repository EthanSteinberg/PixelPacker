set(HDRS
   pixelGui.h
   )

set(SRCS
   pixelGui.cpp
)

add_library(PixelGui ${HDRS} ${SRCS})
target_link_libraries(PixelGui PixelPak ${GTK2_LIBRARIES})
