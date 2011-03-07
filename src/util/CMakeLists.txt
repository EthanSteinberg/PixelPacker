set(HDRS
   myVector2.h
   myBox.h
   )

set(SRCS
   myBox.cpp
   myVector2.cpp
)

add_library(PixelUtil ${HDRS} ${SRCS})
