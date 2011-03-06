#include "myQueue.h"

t_myQueue::t_myQueue(int size) : buffer(size)
{
   if (sem_init(&empty,0,size))
   {
      perror("sem_init empty ");
      exit(1);
   }

   if (sem_init(&full,0,0))
   {
      perror("sem_init full ");
      exit(1);
   }
}


void t_myQueue::push(t_message &message)
{
   if (sem_wait(&empty))
   {
      perror("sem_wait empty ");
      exit(1);
   }

   {
      boost::lock_guard<boost::mutex> lock(mutex);

      buffer.push_back(message);
   }

   if (sem_post(&full))
   {
      perror("sem_wait empty ");
      exit(1);
   }
}


t_message t_myQueue::pop()
{
   t_message temp;

   if (sem_wait(&full))
   {
      perror("sem_wait full2 ");
      exit(1);
   }

   {
      boost::lock_guard<boost::mutex> lock(mutex);

      temp = buffer.front();
      buffer.pop_front();
   }

   if (sem_post(&empty))
   {
      perror("sem_wait empty2 ");
      exit(1);
   }

   return temp;
}
