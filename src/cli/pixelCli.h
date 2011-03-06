#ifndef PIXEL_CLI_H_INCLUDED
#define PIXEL_CLI_H_INCLUDED

#include <boost/utility.hpp>

class t_pixelCli : boost::noncopyable
{
public:

   t_pixelCli();

   void run(int argc, char **argv);
};

#endif
