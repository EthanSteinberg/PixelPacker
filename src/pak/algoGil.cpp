/*
-------------------------------------------------------------------------
This file is part of PixelPacker, tools to pack textures into as small as space as possible.

PixelPacker version 1 of 6 March 2011
Copyright (C) 2011 Ethan Steinberg <ethan.steinberg@gmail.com>

This program is released under the terms of the license contained
in the file COPYING.
---------------------------------------------------------------------------
*/


#include "algoGil.h"
#include <iostream>
#include <vector>
#include <set>
#include <boost/foreach.hpp>
#include <list>

#include <algorithm>

std::multimap<t_myVector2, t_myVector2> t_algoGil::pack(const std::vector< t_myVector2> &temp, const t_myVector2 &size,bool &fine)
{
   std::set<t_myBox> freeBoxes;
   freeBoxes.insert(t_myBox(0,0,size.x,size.y));

   std::list<t_myVector2> rects(temp.begin(), temp.end());

   std::multimap<t_myVector2, t_myVector2> boxes;

   while (!rects.empty())
   {
      int min = std::max(size.x,size.y);

      std::list<t_myVector2>::iterator minIterRects;
      std::set<t_myBox>::iterator minIterFreeBoxes;

      for (auto iterRects = rects.begin(); iterRects != rects.end(); iterRects++)
      {
         for (auto iterFreeBoxes = freeBoxes.begin(); iterFreeBoxes != freeBoxes.end(); iterFreeBoxes++)
         {

            int distance = std::min(iterFreeBoxes->size.y - iterRects->y, iterFreeBoxes->size.x - iterRects->x);
               //std::cout<<"The box "<<iterFreeBoxes->pos<<" with a size "<<iterFreeBoxes->size<<" is too small for "<<*iterRects<<std::endl;

            if (distance < 0)
            {
               continue;
            }

            if (distance < min)
            {
               min = distance;
               minIterRects = iterRects;
               minIterFreeBoxes = iterFreeBoxes;
            }

         }
      }

      //std::cout<<"I am placing the box "<<*minIterRects<<" into the position "<<minIterFreeBoxes->pos<<std::endl;


            t_myBox tempbox(
               t_myVector2(
                  minIterFreeBoxes->pos.x + minIterRects->x,
                  minIterFreeBoxes->pos.y + 0), 
               
               t_myVector2(
                  minIterFreeBoxes->size.x - minIterRects->x, 
                  minIterFreeBoxes->size.y)
               );


            t_myBox tempbox2(
               t_myVector2(
                  minIterFreeBoxes->pos.x + 0,
                  minIterFreeBoxes->pos.y + minIterRects->y), 
               
               t_myVector2(
                  minIterRects->x, 
                  minIterFreeBoxes->size.y - minIterRects->y)
               );


      boxes.insert(std::make_pair(*minIterRects,minIterFreeBoxes->pos));
      freeBoxes.erase(minIterFreeBoxes);
      freeBoxes.insert(tempbox);
      freeBoxes.insert(tempbox2);
      rects.erase(minIterRects);


   }

   fine = 1;
   return boxes;
}

