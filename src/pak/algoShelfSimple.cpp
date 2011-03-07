/*
-------------------------------------------------------------------------
This file is part of PixelPacker, tools to pack textures into as small as space as possible.

PixelPacker version 1 of 6 March 2011
Copyright (C) 2011 Ethan Steinberg <ethan.steinberg@gmail.com>

This program is released under the terms of the license contained
in the file COPYING.
---------------------------------------------------------------------------
*/


#include "algoShelfSimple.h"

#include <boost/foreach.hpp>
#include <iostream>

#include <algorithm>

bool comp(const t_myVector2 &a, const t_myVector2 &b)
{
   return a.y > b.y;
};

std::multimap<t_myVector2, t_myVector2> t_algoShelfSimple::pack(const std::vector< t_myVector2> &temp,const t_myVector2 &size,bool &fine)
{

   std::vector<t_myVector2> rects = temp;
   std::multimap<t_myVector2, t_myVector2> boxes;
   std::vector<t_myVector2> levels;
   std::vector<int> sizes;

   std::sort(rects.begin(), rects.end(),comp);


   //std::cout<<"The boxes are "<<boxes.size()<<std::endl;
   int starty = 0;

   for (unsigned int i = 0; i < rects.size(); i++)
   {
      for (unsigned int b = 0; b< levels.size(); b++)
      {
         if (size.x - levels[b].x >= rects[i].x && sizes[b] >= rects[i].y)
         {
            boxes.insert(std::make_pair(rects[i],levels[b]));
            levels[b].x+= rects[i].x;
            goto done;
         }
      }

      levels.push_back(t_myVector2(rects[i].x,starty));
      sizes.push_back(rects[i].y);
      boxes.insert(std::make_pair(rects[i],t_myVector2(0,starty)));
      starty += rects[i].y;

done:
      ;
   }

   //std::cout<<"Wow at "<<boxes.size()<<std::endl;


   fine = 1;
   return boxes;
}
