/****** Graphics Manager  **********/
/****** Misc Sprite Handling Graphical Options ******/

#ifndef GRAPHICS_MANAGER
#define GRAPHICS_MANAGER

#include "SDL/SDL.h"
#include <iostream>
#

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP 32

namespace gfx 
{
	extern bool hw_accel;
	extern SDL_Surface* main_screen;
}

struct clip
{
	int x, y, w, h;
};

#endif // GRAPHICS_SPRITE