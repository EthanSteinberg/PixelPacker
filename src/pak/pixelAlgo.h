#ifndef PIXEL_ALGO_H_INCLUDED
#define PIXEL_ALGO_H_INCLUDED

#include "myBox.h"
#include "myVector2.h"
#include <vector>
#include <map>

class t_pixelAlgo
{
public:
   virtual std::multimap<t_myVector2, t_myVector2> pack(const std::vector< t_myVector2> &rects, const t_myVector2 &size,bool &fine) = 0;

};

#endif
