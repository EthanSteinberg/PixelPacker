#ifndef MESSAGE_H_INCLUDED
#define MESSAGE_H_INCLUDED

struct t_message
{
   int id;

   union
   {
      int blah;
      double stuff;
   };
};


#endif
