/****** Construct Class - Class For Defining Boundaries **********/
/****** Used To Prevent Sprites From Passing Through Certain Points ******/

#ifndef GRAPHICS_CONSTRUCT
#define GRAPHICS_CONSTRUCT

#include <string>

class Construct
{
	public:

	Construct();
	~Construct();

	std::string target;
	double x, y, height,width;

	double left_bound();
	double right_bound();
	double top_bound();
	double bottom_bound();
}; 

#endif // GRAPHICS_CONSTRUCT