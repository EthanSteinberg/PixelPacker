/*
-------------------------------------------------------------------------
This file is part of PixelPacker, tools to pack textures into as small as space as possible.

PixelPacker version 1 of 6 March 2011
Copyright (C) 2011 Ethan Steinberg <ethan.steinberg@gmail.com>

This program is released under the terms of the license contained
in the file COPYING.
---------------------------------------------------------------------------
*/


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
