/****** Animation Class - Class For Animating Scenes **********/
/****** Handles Animating Various Object In Scenes ******/

#ifndef GRAPHICS_ANIMATION
#define GRAPHICS_ANIMATION

#include <map>
#include "sprite.h"

struct sprite_translation
{
	double start_x, start_y;
	double end_x, end_y;
	double vel_x, vel_y;
	int length, orig_length;
	int priority;
	std::string target;
	bool repeat;
	bool done;
};

class Animation
{
	public :
	
	std::vector <sprite_translation> st_list;
	int current_priority;

	bool st_done;
	
	Animation();
	~Animation();

	void animate_sprite_translations(std::map<std::string, Sprite> &sprite_list);
};

#endif // GRAPHICS_ANIMATION