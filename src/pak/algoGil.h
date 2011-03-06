#ifndef ALGO_GIL_H_INCLUDED
#define ALGO_GIL_H_INCLUDED

#include "pixelAlgo.h"

class t_algoGil : public t_pixelAlgo
{
   public:
   virtual std::multimap<t_myVector2,t_myVector2> pack(const std::vector< t_myVector2> &rects, t_myVector2 &size);
};

#endif
