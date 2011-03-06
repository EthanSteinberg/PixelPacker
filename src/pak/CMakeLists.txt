set(HDRS
   pixelPak.h
   pixelAlgo.h
   algoMaxRects.h
   algoShelfSimple.h
   algoGil.h
   )

set(SRCS
   pixelPak.cpp
   algoMaxRects.cpp
   algoShelfSimple.cpp
   algoGil.cpp
)

add_library(PixelPak ${HDRS} ${SRCS})
target_link_libraries(PixelPak PixelUtil ${MAGICK++_LIBRARIES})
