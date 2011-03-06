set(HDRS
   myVector2.h
   myBox.h
   myQueue.h
   message.h
   )

set(SRCS
   myBox.cpp
   myVector2.cpp
   myQueue.cpp
)

add_library(PixelUtil ${HDRS} ${SRCS})
