/****** Init **********/
/****** Sets up & Prepares Key Game Items ******/

#ifndef INIT
#define INIT

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_opengl.h"
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include "Graphics/sprite.h"
#include "Graphics/gfx_manager.h"
#include "Input/input.h"

bool opengl_init();
bool init();
void parse_cli_args(std::string arg);

namespace var 
{
	extern int frame_start_time, frame_current_time, frame_count;
	extern bool quit;
}

#endif // INIT