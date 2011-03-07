#ifndef ALGO_SHELF_SIMPLE_H_INCLUDED
#define ALGO_SHELF_SIMPLE_H_INCLUDED

#include "pixelAlgo.h"

class t_algoShelfSimple : public t_pixelAlgo
{
   public:
   virtual std::multimap<t_myVector2, t_myVector2> pack(const std::vector< t_myVector2> &rects, const t_myVector2 &size,bool &fine);
};

#endif
