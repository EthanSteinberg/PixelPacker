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
