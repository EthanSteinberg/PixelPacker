/*
-------------------------------------------------------------------------
This file is part of PixelPacker, tools to pack textures into as small as space as possible.

PixelPacker version 1 of 6 March 2011
Copyright (C) 2011 Ethan Steinberg <ethan.steinberg@gmail.com>

This program is released under the terms of the license contained
in the file COPYING.
---------------------------------------------------------------------------
*/


#ifndef MY_QUEUE_H_INCLUDED
#define MY_QUEUE_H_INCLUDED

#include <boost/utility.hpp>

#include <semaphore.h>
#include <boost/thread.hpp>
#include <boost/circular_buffer.hpp>

#include "message.h"

class t_myQueue : boost::noncopyable
{
public:
   t_myQueue(int size = 100);

   void push(t_message &message);

   t_message pop();

private:
   sem_t empty;
   sem_t full;

   boost::mutex mutex;
   boost::circular_buffer<t_message> buffer;
};


#endif
