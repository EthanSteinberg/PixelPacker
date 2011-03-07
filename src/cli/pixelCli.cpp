/*
-------------------------------------------------------------------------
This file is part of PixelPacker, tools to pack textures into as small as space as possible.

PixelPacker version 1 of 6 March 2011
Copyright (C) 2011 Ethan Steinberg <ethan.steinberg@gmail.com>

This program is released under the terms of the license contained
in the file COPYING.
---------------------------------------------------------------------------
*/


#include "pixelCli.h"
#include "../pak/pixelPak.h"
#include "../pak/algoShelfSimple.h"
#include "../pak/algoGil.h"
#include "../pak/algoMaxRects.h"

#include <vector>
#include <string>
#include <boost/program_options.hpp>
#include <boost/foreach.hpp>
#include <iostream>
#include <fstream>

namespace po = boost::program_options;

t_pixelCli::t_pixelCli()
{}

void t_pixelCli::run(int argc, char **argv)
{
   std::string outputName;

   po::options_description desc;

   desc.add_options()
      ("help,h", "Produce a help message")
      ("output,o",po::value<std::string>(&outputName)->default_value("pixelPacker"), "Name for the output. The image is THIS.png, the json file is THIS.json")
      ("input",po::value<std::vector<std::string> >(),"Takes the list of files to process")
      ("algorithm,a",po::value<int>()->default_value(0),"Which algorithm to use, currently supported:\n\nMaxRects: 0:\t Slow but generally best packing\n\nGuilitine 1:\t Faster than maxRects, but worse packing\n\nShelf 2:\t The fastest algorithm by far, but does use space effeciently")
      ("readable,r",po::value<bool>()->default_value(true),"Should the json output be readable?")
      ;

   po::positional_options_description p;
   p.add("input", -1);

   po::variables_map vm;

   po::store(po::command_line_parser(argc, argv).
                   options(desc).positional(p).run(), vm);
   po::notify(vm);

   if (vm.count("help"))
   {
      std::cout<<"PixelPacker [options] <list of files> \n\nOptions:\n ";
      std::cout<<desc<<'\n';
      return;
   }

   if (vm.count("input"))
   {
      std::vector<std::string> strings = vm["input"].as<std::vector<std::string> >();

      /*
      BOOST_FOREACH(std::string &b , strings)
      {
         std::cout<<b<<std::endl;
      }
      */

      t_pixelPak packer;
      switch(vm["algorithm"].as<int>())
      {
         case 0:
            packer = t_pixelPak(new t_algoMaxRects   ,vm["readable"].as<bool>());
            break;

         case 1:
            packer = t_pixelPak(new t_algoGil        ,vm["readable"].as<bool>());
            break;

         case 2:
            packer = t_pixelPak(new t_algoShelfSimple,vm["readable"].as<bool>());
            break;
      }

        std::pair<Magick::Image, std::string> output = packer.process(strings);
      Magick::Image myPic = output.first;
      std::string jsonData = output.second;

      myPic.write(outputName + ".png");
      
      std::ofstream out(outputName + ".json");
      out<<jsonData;

      return;
   }
}
