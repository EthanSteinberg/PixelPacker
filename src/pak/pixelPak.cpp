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

#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>
#include <algorithm>
#include <map>
#include <cmath>
#include <iostream>

#include <assert.h>
#include <json/value.h>
#include <json/writer.h>


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


t_pixelPak::t_pixelPak(t_pixelAlgo *anAlgorithm,bool isReadable) : algo(anAlgorithm), readable(isReadable)
{
}

std::pair<Magick::Image,std::string> t_pixelPak::process(const std::vector<std::string> &files)
{
   std::vector<t_myVector2> images;
   std::vector<Magick::Image> tempImages;

   t_myVector2 tempBox;
   //int max = 0;
   int areaSum = 0;

   BOOST_FOREACH(const std::string &name, files)
   {
      Magick::Image tempImage;
      tempImage.read(name);

      //Magick::Color temp = tempImage.pixelColor(0,0);
      //   std::cout<<(std::string)temp<<std::endl;
      //tempImage.transparent(temp);
      //tempImage.type(Magick::TrueColorMatteType);

      tempImage.trim();

      tempBox.y = tempImage.rows()+1;
      tempBox.x = tempImage.columns()+1;

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

   boxes = algo->pack(images, size,fine);

   if (!fine)
   {
      std::cout<<"The smaller size was not enouph, bumping up"<<std::endl;
      size.y = nextHigh;
      boxes = algo->pack(images,size,fine);
   }


   Magick::ColorMono clear(true);
   clear.alpha(0.0);
   Magick::Image output(Magick::Geometry(size.x,size.y),"#000000FF");

   Json::Value rootNode(Json::ValueType::objectValue);
   rootNode["sizex"] =  Json::Value(size.x);
   rootNode["sizey"] =  Json::Value(size.y);


   {
      // std::cout<<"About to composite "<<boxes.size()<<std::endl;
      for (unsigned int i = 0; i< files.size(); i ++)
      {
         Magick::Image tempImage(tempImages[i]);

         auto iter = boxes.find(images[i]);
         t_myVector2 pos = iter->second;
         boxes.erase(iter);

         output.composite(tempImage,pos.x,pos.y,Magick::OverCompositeOp);
         //      std::cout<<"I have composed "<<i<<std::endl;

         boost::filesystem::path imagePath(files[i]);
         std::string imageName = imagePath.stem().native();

         Json::Value imageNode(Json::ValueType::objectValue);
         imageNode["x"] = Json::Value(pos.x);
         imageNode["y"] = Json::Value(pos.y);
         imageNode["sizex"] = Json::Value(images[i].x);
         imageNode["sizey"] = Json::Value(images[i].y);


         rootNode[imageName] = imageNode;

      }
   }


   std::string jsonData;

   if (readable)
   {
      Json::StyledWriter writer;
      jsonData = writer.write(rootNode);
   }

   else
   {
      Json::FastWriter writer;
      jsonData = writer.write(rootNode);
   }


   return std::make_pair(output,jsonData);

}

