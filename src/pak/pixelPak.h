/*
-------------------------------------------------------------------------
This file is part of PixelPacker, tools to pack textures into as small as space as possible.

PixelPacker version 1 of 6 March 2011
Copyright (C) 2011 Ethan Steinberg <ethan.steinberg@gmail.com>

This program is released under the terms of the license contained
in the file COPYING.
---------------------------------------------------------------------------
*/


#ifndef PIXEL_PAK_H_INCLUDED
#define PIXEL_PAK_H_INCLUDED

#include <boost/utility.hpp>

#include "pixelAlgo.h"
#include "algoMaxRects.h"
#include <vector>
#include <string>
#include <Magick++.h>

class t_pixelPak
{
   public:
      t_pixelPak(t_pixelAlgo *algorithm = new t_algoMaxRects(),bool readable = true);

      std::pair<Magick::Image, std::string> process(const std::vector<std::string> &files);

   private:
      t_pixelAlgo *algo;
      bool readable;
};

#endif
