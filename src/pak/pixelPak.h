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
