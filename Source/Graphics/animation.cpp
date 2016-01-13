/****** Animation Class - Class For Animating Scenes **********/
/****** Handles Animating Various Object In Scenes ******/

#include "animation.h"

Animation::Animation() { }

Animation::~Animation() { }

/****** Translate Sprites ******/
void Animation::animate_sprite_translations(std::map<std::string, Sprite> &sprite_list) 
{
	bool priority_jump;

	/* Loop through entire Translation List */
	for(int x = -1; ++x < st_list.size();)
	{
		/* Reset priority jump test at start of loop */
		if(x == 0) { priority_jump = true; }

		/* If this translation's priority matches the current priority, start translation */
		if(((st_list[x].priority == current_priority) && (st_list[x].done == false)) || (st_list[x].repeat == true))
		{
			sprite_list[st_list[x].target].orig_x += st_list[x].vel_x;
			sprite_list[st_list[x].target].orig_y += st_list[x].vel_y;
			st_list[x].length--;
			priority_jump = false;	
			
			/* Finish the translation */
			if((st_list[x].length == 0) && (st_list[x].repeat == false)) { st_list[x].done = true; }

			/* Or repeat the translation */
			else if((st_list[x].length == 0) && (st_list[x].repeat == true)) 
			{ 
				st_list[x].length = st_list[x].orig_length;
				sprite_list[st_list[x].target].orig_x = st_list[x].start_x;
				sprite_list[st_list[x].target].orig_y = st_list[x].start_y;
			}
			
			if(st_list[x].length == 0) {std::cout<<"Repeat : " << st_list[x].repeat << "\n"; }

		}

		/* Determine if current priority needs to be increased - All current animations finished? */
		if((x == (st_list.size() - 1)) && (priority_jump)) { current_priority++; }
	}
}