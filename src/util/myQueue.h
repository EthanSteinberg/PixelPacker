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
