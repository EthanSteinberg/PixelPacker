#include "myBox.h"
#include <utility>

using namespace std::rel_ops;

t_myBox::t_myBox()
{}

t_myBox::t_myBox(int x,int y, int width, int height) : pos(x,y), size(width,height)
{}

t_myBox::t_myBox(t_myVector2 Pos, t_myVector2 Size) : pos(Pos), size(Size)
{}

bool t_myBox::operator==(const t_myBox &box) const
{
   return (box.pos == pos) && (box.size == size);
}

bool t_myBox::operator<(const t_myBox &box) const
{
   if (box.pos < pos)
   {
      return 1;
   }

   else if (box.pos >  pos)
   {
      return 0;
   }

   else if (box.size < size)
   {
      return 1;
   }

   else
   {
      return 0;
   }
}
