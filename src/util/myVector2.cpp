#include "myVector2.h"
#include <utility>

using namespace std::rel_ops;

t_myVector2::t_myVector2()
{}

t_myVector2::t_myVector2(int X, int Y)
{
   x = X;
   y = Y;
}

std::ostream &operator<<(std::ostream &out, const t_myVector2 &vec2)
{
   out<<"X: "<<vec2.x<<" Y:"<<vec2.y;
   return out;
}

bool t_myVector2::operator==(const t_myVector2 &vec) const
{
   return (vec.x == x) && (vec.y == y);
}

bool t_myVector2::operator<(const t_myVector2 &vec) const
{
   if (vec.x < x)
      return 1;

   else if (vec.x > x)
      return 0;

   else if (vec.y < y)
      return 1;

   else 
      return 0;
}
