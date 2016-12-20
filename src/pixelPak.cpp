/*
-------------------------------------------------------------------------
This file is part of PixelPacker, tools to pack textures into as small as space as possible.

PixelPacker version 1 of 6 March 2011
Copyright (C) 2011 Ethan Steinberg <ethan.steinberg@gmail.com>

This program is released under the terms of the license contained
in the file COPYING.
---------------------------------------------------------------------------
*/


#include "pixelPak.h"
#include "myBox.h"
#include "algoMaxRects.h"

#include <algorithm>
#include <map>
#include <cmath>
#include <iostream>

#include <assert.h>

#include <json.hpp>

#include <lodepng.h>

template <class T>
T nearestpower2(T v)
{
   int k;

   if (v == 0)
   {
      return 1;
   }

   for (k = sizeof(T) * 8 - 1; ((static_cast<T>(1U) << k) & v) == 0; k--);

   if (((static_cast<T>(1U) << (k - 1)) & v) == 0)
   {
      return static_cast<T>(1U) << k;
   }

   return static_cast<T>(1U) << (k + 1);
}


template <class T>
T nexthigher(T k)
{
   k--;

   for (unsigned int i=1; i<sizeof(T)*8; i<<=1)
   {
      k = k | k >> i;
   }

   return k+1;
}


std::pair<Image, std::string> process(const std::vector<std::string> &files)
{
   std::vector<t_myVector2> images;
   std::vector<Image> tempImages;

   t_myVector2 tempBox;
   //int max = 0;
   int areaSum = 0;

   for (const std::string& name: files) {
      Image tempImage;

      unsigned error = lodepng::decode(tempImage.pixels, tempImage.width, tempImage.height, name);

      if (error) {
         std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
      }

      tempBox.x = tempImage.width+1;
      tempBox.y = tempImage.height+1;

      //max = std::max(tempBox.x,max);
      //max = std::max(tempBox.y,max);
      // std::cout<<tempBox<<std::endl;
      images.push_back(tempBox);
      tempImages.push_back(tempImage);

      areaSum += tempBox.y * tempBox.x;
   }

   //std::cout<<areaSum<<std::endl;
   int side = sqrt(areaSum);
   int nextHigh = nexthigher(side);
   int nextNear = nearestpower2(side);
   t_myVector2 size(nextHigh, nextNear);
   std::cout<<"The size was "<<size<<" with an area of "<<(int) sqrt(areaSum)<<std::endl;
   std::multimap<t_myVector2, t_myVector2> boxes;

   bool fine = 0;

   boxes = pack(images, size, fine);

   while (!fine)
   {
      std::cout<<"The smaller size was not enouph, bumping up"<<std::endl;
      size.x *= 2;
      size.y *= 2;
      boxes = pack(images, size, fine);
   }

   std::vector<unsigned char> output(size.x * size.y * 4);

   nlohmann::json rootNode;
   rootNode["sizex"] =  size.x;
   rootNode["sizey"] =  size.y;

   for (unsigned int i = 0; i< files.size(); i ++) {
      const Image &tempImage = tempImages[i];

      auto iter = boxes.find(images[i]);
      t_myVector2 pos = iter->second;
      boxes.erase(iter);

      for (unsigned int x = 0; x < tempImage.width; x++) {
         for (unsigned int y = 0; y < tempImage.height; y++) {
            for (int c = 0; c < 4; c++) {
               output[(y + pos.y) * size.x * 4 + (x + pos.x) * 4 + c] = tempImage.pixels[y * tempImage.width * 4 + x * 4 + c];
            }
         }
      }

      int posOfDot = files[i].find('.');
      std::string imageName = files[i].substr(0, posOfDot);

      nlohmann::json imageNode;
      imageNode["x"] = pos.x;
      imageNode["y"] = pos.y;
      imageNode["sizex"] = images[i].x - 1;
      imageNode["sizey"] = images[i].y - 1;

      rootNode[imageName] = imageNode;
   }

   std::string jsonData = rootNode.dump(4);

   Image result;
   result.pixels = std::move(output);
   result.width = size.x;
   result.height = size.y;

   return std::make_pair(result,jsonData);
}