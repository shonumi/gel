/****** Input  **********/
/****** Handles All Input Actions From Keyboards & Joysticks ******/

#include "input.h"

namespace ctrl
{
	bool left, right, up, down, button1, button2 = false;
	int left_pad, right_pad, up_pad, down_pad, button1_pad, button2_pad = 0;
}

/****** Handles All Input ******/
bool handle_input(SDL_Event &event, Scene &current_scene) {

	/* Window Resize Event - OpenGL */
	if((event.type == SDL_VIDEORESIZE) && (gfx::hw_accel))
	{
		Sprite::x_ratio = event.resize.w/640.0;
		Sprite::y_ratio = event.resize.h/480.0;

		glViewport(0, 0, event.resize.w, event.resize.h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glOrtho(0, event.resize.w, event.resize.h, 0, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		SDL_SetVideoMode(event.resize.w, event.resize.h, SCREEN_BPP, SDL_RESIZABLE | SDL_OPENGL);
	}

	/* Key Down Event Capture */
	else if(event.type == SDL_KEYDOWN)
	{
		if(event.key.keysym.sym == ctrl::left_pad) { ctrl::left = true; }
		else if(event.key.keysym.sym == ctrl::right_pad) { ctrl::right = true; }
		else if(event.key.keysym.sym == ctrl::up_pad) { ctrl::up = true; }
		else if(event.key.keysym.sym == ctrl::down_pad) { ctrl::down = true; }
		else if(event.key.keysym.sym == ctrl::button1_pad) { ctrl::button1 = true; }
		else if(event.key.keysym.sym == ctrl::button2_pad) { ctrl::button2 = true; }

		/* Handle Scene Button Events */
		for(int x = -1; ++x < current_scene.scene_button_list.size();)
		{
			std::string s_file = current_scene.scene_button_list[x].next_scene_file;
			if((ctrl::left) && (current_scene.scene_button_list[x].pad == "LEFT")) { current_scene.load_scene(s_file); }
			else if((ctrl::right) && (current_scene.scene_button_list[x].pad == "RIGHT")) { current_scene.load_scene(s_file); }
			else if((ctrl::up) && (current_scene.scene_button_list[x].pad == "UP")) { current_scene.load_scene(s_file); }
			else if((ctrl::down) && (current_scene.scene_button_list[x].pad == "DOWN")) { current_scene.load_scene(s_file); }
			else if((ctrl::button1) && (current_scene.scene_button_list[x].pad == "BUTTON1")) { current_scene.load_scene(s_file); }
			else if((ctrl::button2) && (current_scene.scene_button_list[x].pad == "BUTTON2")) { current_scene.load_scene(s_file); }
		}

		/* Handle Scene Button Range Events */
		for(int x = -1; ++x < current_scene.scene_button_range_list.size();)
		{
			if(current_scene.scene_button_range_list[x].in_range)
			{
				std::string s_file = current_scene.scene_button_range_list[x].next_scene_file;
				if((ctrl::left) && (current_scene.scene_button_range_list[x].pad == "LEFT")) 
				{ 
					current_scene.load_scene(s_file); 
					current_scene.scene_button_range_list[x].in_range = false; 
				}
				
				else if((ctrl::right) && (current_scene.scene_button_range_list[x].pad == "RIGHT")) 
				{ 
					current_scene.load_scene(s_file); 
					current_scene.scene_button_range_list[x].in_range = false; 
				}
				
				else if((ctrl::up) && (current_scene.scene_button_range_list[x].pad == "UP")) 
				{ 
					current_scene.load_scene(s_file); 
					current_scene.scene_button_range_list[x].in_range = false; 
				}
				
				else if((ctrl::down) && (current_scene.scene_button_range_list[x].pad == "DOWN")) 
				{ 
					current_scene.load_scene(s_file); 
					current_scene.scene_button_range_list[x].in_range = false; 
				}

				else if((ctrl::button1) && (current_scene.scene_button_range_list[x].pad == "BUTTON1")) 
				{ 
					current_scene.load_scene(s_file); 
					current_scene.scene_button_range_list[x].in_range = false;
				}
				
				else if((ctrl::button2) && (current_scene.scene_button_range_list[x].pad == "BUTTON2")) 
				{
					current_scene.load_scene(s_file); 
					current_scene.scene_button_range_list[x].in_range = false;
				}
			}
		}
	}

	/* Key Up Event Capture */
	else if(event.type == SDL_KEYUP)
	{
		if(event.key.keysym.sym == ctrl::left_pad) { ctrl::left = false; }
		else if(event.key.keysym.sym == ctrl::right_pad) { ctrl::right = false; }
		else if(event.key.keysym.sym == ctrl::up_pad) { ctrl::up = false; }
		else if(event.key.keysym.sym == ctrl::down_pad) { ctrl::down = false; }
		else if(event.key.keysym.sym == ctrl::button1_pad) { ctrl::button1 = false; }
		else if(event.key.keysym.sym == ctrl::button2_pad) { ctrl::button2 = false; }
	}

	/*  Application Quit Event */           
	else if(event.type == SDL_QUIT) { return true; }

	return false;
}

/****** Load XGL controls config ******/
bool load_controller_config(std::string config_file)
{
	std::vector <int> temp_vec;

	/* Attempt to read input configuration XGL file to temporary vector */
	if(!parse_xgl_int(config_file, temp_vec))
	{
		std::cout<<"The controller configuration file : " << config_file << " failed to load \n";
		return false;
	}

	ctrl::left_pad = temp_vec[0];
	ctrl::right_pad = temp_vec[1];
	ctrl::up_pad = temp_vec[2];
	ctrl::down_pad = temp_vec[3];
	ctrl::button1_pad = temp_vec[4];
	ctrl::button2_pad = temp_vec[5];

	return true;
}

/****** Move Player when in overworld ******/
void move_player_overworld(Sprite &player, Scene &current_scene)
{
	Construct temp_con;
	bool collide = true;

	if(ctrl::left) { player.orig_x -= 3; }
	if(ctrl::right) { player.orig_x += 3; }
	if(current_scene.construct_list.size() < 1) { collide = false; }

	/* Check for construct collisions */
	for(int x = -1; ++x < current_scene.construct_list.size();)
	{
		temp_con = current_scene.construct_list[x];
		
		if(player.left_bound() > temp_con.right_bound()) { collide = false; }
		if(player.right_bound() < temp_con.left_bound()) { collide = false; }
		if(player.top_bound() > temp_con.bottom_bound()) { collide = false; }
		if(player.bottom_bound() < temp_con.top_bound()) { collide = false; }
	}

	if((collide) && (ctrl::left)) { player.current_frame = 5; player.orig_x += 3;}
	else if((!collide) && (ctrl::left)) { player.animate(5, 8, 12); } 

	else if((collide) && (ctrl::right)) { player.current_frame = 1; player.orig_x -= 3;}
	else if((!collide) && (ctrl::right)) { player.animate(1, 4, 12); } 

	else if(!collide) { player.current_frame = 0; }
}
