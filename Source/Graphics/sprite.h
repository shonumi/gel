/****** Sprite Class - Base Class For All Interactive Graphics **********/
/****** Handles Graphics Level Details For Other Derived Classes ******/

#ifndef GRAPHICS_SPRITE
#define GRAPHICS_SPRITE

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_opengl.h"
#include <iostream>
#include <string>
#include "gfx_manager.h"
#include "Core/xgl.h"

class Sprite 
{
	public:
    
	double x, y; 
	double orig_x, orig_y;
	double width, height;
	double orig_w, orig_h;
	double rotate;
	GLuint current_texture;
	SDL_Surface* current_surface;
	int current_frame;
	int frame_spacer;
	std::vector<clip> sprite_clip;
	bool clipped;
	
	static double x_ratio, y_ratio;

	Sprite();
	Sprite(double x_pos, double y_pos, double w, double h, std::string image);
	~Sprite();

	bool load_texture(std::string image);
	bool load_clips(std::string clip_file);
	void animate(int start, int end, int timing);
	virtual void draw();

	double left_bound();
	double right_bound();
	double top_bound();
	double bottom_bound();
};

#endif // GRAPHICS_SPRITE