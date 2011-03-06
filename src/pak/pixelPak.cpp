#include "pixelPak.h"
#include "myBox.h"

#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>
#include <algorithm>
#include <map>
#include <iostream>

#include <assert.h>
#include <json/value.h>
#include <json/writer.h>




t_pixelPak::t_pixelPak(t_pixelAlgo *anAlgorithm,bool isReadable) : algo(anAlgorithm), readable(isReadable)
{
}

std::pair<Magick::Image,std::string> t_pixelPak::process(const std::vector<std::string> &files)
{
   std::vector<t_myVector2> images;
   std::vector<Magick::Image> tempImages;

   t_myVector2 tempBox;
   //int max = 0;
   //int areaSum = 0;
   try
   {
      BOOST_FOREACH(const std::string &name, files)
      {
         Magick::Image tempImage;
         tempImage.read(name);

         Magick::Color temp = tempImage.pixelColor(0,0);
      //   std::cout<<(std::string)temp<<std::endl;
         tempImage.transparent(temp);
         tempImage.type(Magick::TrueColorMatteType);

         tempImage.trim();

         tempBox.y = tempImage.rows();
         tempBox.x = tempImage.columns();

         //max = std::max(tempBox.x,max);
         //max = std::max(tempBox.y,max);
        // std::cout<<tempBox<<std::endl;
         images.push_back(tempBox);
         tempImages.push_back(tempImage);

         //areaSum += tempBox.y * tempBox.x;
      }
   }

   catch(std::exception &ec)
   {
      std::cout<<"I have an exception"<<std::endl;
      std::cout<<ec.what()<<std::endl;
      exit(1);
   }
   

   //std::cout<<areaSum<<std::endl;
   t_myVector2 size;
   std::multimap<t_myVector2, t_myVector2> boxes = algo->pack(images, size);

   Magick::ColorMono clear(true);
   clear.alpha(0.0);
   Magick::Image output(Magick::Geometry(4096,4096),"#000000FF");

   Json::Value rootNode(Json::ValueType::objectValue);


   try
   {
     // std::cout<<"About to composite "<<boxes.size()<<std::endl;
      for (unsigned int i = 0; i< files.size();i ++)
      {
         Magick::Image tempImage(tempImages[i]);
         
         auto iter = boxes.find(images[i]);
         t_myVector2 pos = iter->second;
         boxes.erase(iter);

         output.composite(tempImage,pos.x,pos.y,Magick::OverCompositeOp);
   //      std::cout<<"I have composed "<<i<<std::endl;
         
         boost::filesystem::path imagePath(files[i]);
         std::string imageName = imagePath.stem();

         Json::Value imageNode(Json::ValueType::objectValue);
         imageNode["x"] = Json::Value(pos.x);
         imageNode["y"] = Json::Value(pos.y);
         imageNode["sizex"] = Json::Value(images[i].x);
         imageNode["sizey"] = Json::Value(images[i].y);


         rootNode[imageName] = imageNode;
      
      }
   }



   catch(std::exception &ec)
   {
      std::cout<<"I have an exception"<<std::endl;
      std::cout<<ec.what()<<std::endl;
      exit(1);
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

