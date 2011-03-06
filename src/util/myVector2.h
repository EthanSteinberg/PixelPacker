#ifndef MY_VECTOR_2_H_INCLUDED
#define MY_VECTOR_2_H_INCLUDED

#include <ostream>

class t_myVector2
{
public:
   t_myVector2();
   t_myVector2(int x, int y);

   friend std::ostream& operator<<(std::ostream &out, const t_myVector2 &vec2);

   bool operator==(const t_myVector2 &vec) const;
   bool operator<(const t_myVector2 &vec) const;

   int x;
   int y;
};


#endif
