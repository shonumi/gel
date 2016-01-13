/****** Construct Class - Class For Defining Boundaries **********/
/****** Used To Prevent  From Passing Through Certain Points ******/

#include "construct.h"

Construct::Construct() 
{
	target = "";
	x = 0;
	y = 0;
 	height = 0;
	width = 0; 
}

Construct::~Construct() { }

/****** Returns the left boundary of a Construct ******/
double Construct::left_bound() { return x; }

/****** Returns the right boundary of a Construct ******/
double Construct::right_bound() { return (x + width); }

/****** Returns the true top boundary of a Construct ******/
double Construct::top_bound() { return y; }

/****** Returns the true bottom boundary of a Construct ******/
double Construct::bottom_bound() { return y + height; } 
