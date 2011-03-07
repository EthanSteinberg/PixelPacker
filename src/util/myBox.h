/*
-------------------------------------------------------------------------
This file is part of PixelPacker, tools to pack textures into as small as space as possible.

PixelPacker version 1 of 6 March 2011
Copyright (C) 2011 Ethan Steinberg <ethan.steinberg@gmail.com>

This program is released under the terms of the license contained
in the file COPYING.
---------------------------------------------------------------------------
*/


#ifndef MY_BOX_H_INCLUDED
#define MY_BOX_H_INCLUDED

#include "myVector2.h"

class t_myBox
{
public:
   t_myBox();
   t_myBox(int x, int y, int width, int height);
   t_myBox(t_myVector2 pos,t_myVector2 size);

   bool operator==(const t_myBox &box) const;
   bool operator<(const t_myBox &box) const;

   t_myVector2 pos;
   t_myVector2 size;
};


#endif
