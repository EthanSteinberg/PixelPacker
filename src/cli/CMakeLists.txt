set(HDRS
   pixelCli.h
   )

set(SRCS
   pixelCli.cpp
)

add_library(PixelCli ${HDRS} ${SRCS})
target_link_libraries(PixelCli PixelPak)
