/****** Init **********/
/****** Sets up & Prepares Key Game Items ******/

#include "init.h"

namespace var 
{
	int frame_start_time, frame_current_time, frame_count = 0;
	bool quit = false;
}


/****** Initializes Core OpenGL Features ******/
bool opengl_init() 
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0, 0, 0, 0);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if(glGetError() != GL_NO_ERROR) { return false; }

	return true;
}

/****** Initializes SDL, OpenGL and Video and Window ******/
bool init()
{
    
	/* Initialize All SDL Systems */
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout<<"SDL could not be initialized!\n";
		return false;    
	}

	/* Use OpenGL for Rendering */
	if(gfx::hw_accel)
	{
		/* Initialize SDL Video - OpenGL */
		if(SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_RESIZABLE | SDL_OPENGL) == NULL) 
		{
			std::cout<<"SDL Video could not be initialized!\n";
			return false;
		}

		/* Initialize OpenGL */
		if(opengl_init() == false) 
		{
			std::cout<<"OpenGL could not be initialized!\n";
			return false;
		}

		std::cout<<"Renderer - OpenGL \n";
	}

	/* Use SDL for Rendering */
	else 
	{
		/* Initialize SDL Video - SDL */
		gfx::main_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

		if(gfx::main_screen == NULL)
		{
			std::cout<<"SDL Video could not be initialized!\n";
			return false;
		}

		std::cout<<"Renderer - SDL \n";
	}
		
 
	/* Initialize TTF */
	if(TTF_Init() == -1) 
	{
		std::cout<<"SDL TTF could not be initialized\n";
		return false; 
	}

	/* Load controller configuration */
	if(!load_controller_config("Config/controls.xgl")) { return false; }

	SDL_WM_SetCaption("RPG Game - Development", NULL);

	/* Print other info */
	std::cout<<"RPG Game copyright Daniel & Alex Baxter 2012\n";
	std::cout<<"Version 0.1 " << __DATE__ << " " << __TIME__ << "\n";

	return true;
}

/****** Parse CLI Arguments ******/
void parse_cli_args(std::string arg)
{
	if(arg == "-sdl") { gfx::hw_accel = false; }

	else { std::cout<<"Unrecognized argument : " << arg << "\n"; }
}
