/****** Scene Class - Class For Graphical Scenes **********/
/****** Handles Loading And Managing Individual Scenes ******/

#include "scene.h"

Scene::Scene() { }

Scene::~Scene() { }

/****** Load scene from XGL file******/
bool Scene::load_scene(std::string scene_file)
{
	/* Clear previous scene information */
	sprite_list.clear();
	text_list.clear();
	scene_button_list.clear();
	scene_range_list.clear();
	scene_button_range_list.clear();
	construct_list.clear();
	
	animator.current_priority = 1;
	animator.st_list.clear();
	animator.st_done = false;

	/* Attempt to load XGL scene file to temporary vector */
	std::vector <std::string> temp_vec;
	if(!parse_xgl_string(scene_file, temp_vec))
	{
		std::cout<<"The scene file : " << scene_file << " failed to load\n";
		return false;
	}

	/* Parse XGL to create scene */
	for(int x = 0; x < temp_vec.size();)
	{
		/* Parse sprites */
		if(temp_vec[x] == "SPRITE")
		{
			/* Temp doubles converted from strings, x, y, w, h*/
			double sx = numparse(temp_vec[x+2]);
			double sy = numparse (temp_vec[x+3]);
			double sw = numparse(temp_vec[x+4]);
			double sh = numparse(temp_vec[x+5]);

			Sprite temp_sprite(sx, sy, sw, sh, temp_vec[x+6]);
			
			/* Clip sprite if necessary */
			if(temp_vec[x+7] != "no_clip") { 
				if(!temp_sprite.load_clips(temp_vec[x+7])) { return false; }
			}	

			sprite_list[temp_vec[x+1]] = temp_sprite;
			x += 8;
		}

		/* Parse text */
		else if(temp_vec[x] == "TEXT")
		{
			/* Temps coverted from strings x, y, delay */
			double sx = numparse(temp_vec[x+1]);
			double sy = numparse(temp_vec[x+2]);
			int sd = int(numparse(temp_vec[x+3]));

			Text temp_text(sx, sy, sd, temp_vec[x+4], font_list[temp_vec[x+5]], temp_vec[x+6]);
			text_list.push_back(temp_text);
			x += 7;
		}

		/* Parse scene buttons */
		else if(temp_vec[x] == "SCENE_BUTTON")
		{
			scene_button temp_sb;
			
			temp_sb.next_scene_file = temp_vec[x+1];
			temp_sb.pad = temp_vec[x+2];

			scene_button_list.push_back(temp_sb);
			x += 3;
		}

		/* Parse scene ranges */
		else if(temp_vec[x] == "SCENE_RANGE")
		{
			scene_range temp_sr;

			temp_sr.next_scene_file = temp_vec[x+1];
			temp_sr.target = temp_vec[x+2];
			temp_sr.min_x = numparse(temp_vec[x+3]);
			temp_sr.min_y = numparse(temp_vec[x+4]);
			temp_sr.max_x = numparse(temp_vec[x+5]);
			temp_sr.max_y = numparse(temp_vec[x+6]);

			scene_range_list.push_back(temp_sr);
			x += 7;
		}

		/* Parse scene button ranges */
		else if(temp_vec[x] == "SCENE_BUTTON_RANGE")
		{
			scene_button_range temp_sbr;

			temp_sbr.next_scene_file = temp_vec[x+1];
			temp_sbr.pad = temp_vec[x+2];
			temp_sbr.target = temp_vec[x+3];
			temp_sbr.min_x = numparse(temp_vec[x+4]);
			temp_sbr.min_y = numparse(temp_vec[x+5]);
			temp_sbr.max_x = numparse(temp_vec[x+6]);
			temp_sbr.max_y = numparse(temp_vec[x+7]);
			temp_sbr.in_range = false;

			scene_button_range_list.push_back(temp_sbr);
			x += 8;
		}
			
		/* Parse constructs */
		else if(temp_vec[x] == "CONSTRUCT")
		{
			Construct temp_con;

			/* Attach construct to previously defined sprite */
			if(temp_vec[x+1] != "no_sprite")
			{
				temp_con.x = sprite_list[temp_vec[x+1]].left_bound();
				temp_con.y = sprite_list[temp_vec[x+1]].top_bound();
				temp_con.width = sprite_list[temp_vec[x+1]].orig_w;
				temp_con.height = sprite_list[temp_vec[x+1]].orig_h;
				x += 2;
			}

			/* Generate transparent construct */
			else
			{
				temp_con.target = temp_vec[x+1];
				temp_con.x = numparse(temp_vec[x+2]);
				temp_con.y = numparse(temp_vec[x+3]);
				temp_con.width = numparse(temp_vec[x+4]);
				temp_con.height = numparse(temp_vec[x+5]);
				x += 6;
			}
		
			construct_list.push_back(temp_con);
		}

		/* Parse Animation - Sprite Translations */
		else if(temp_vec[x] == "TRANSLATE_SPRITE")
		{
			sprite_translation temp_st;
			temp_st.done = false;

			temp_st.target = temp_vec[x+1];
			temp_st.priority = numparse(temp_vec[x+2]);
			temp_st.length = numparse(temp_vec[x+7]);
			temp_st.orig_length = temp_st.length;

			temp_st.start_x = numparse(temp_vec[x+3]);
			temp_st.start_y = numparse(temp_vec[x+4]);
			temp_st.end_x = numparse(temp_vec[x+5]);
			temp_st.end_y = numparse(temp_vec[x+6]);
			temp_st.vel_x = (temp_st.end_x - temp_st.start_x)/temp_st.length;
			temp_st.vel_y = (temp_st.end_y - temp_st.start_y)/temp_st.length;
			
			if(temp_vec[x+8] == "repeat") { temp_st.repeat = true; }
			else if(temp_vec[x+8] == "no_repeat") { temp_st.repeat = false; }

			animator.st_list.push_back(temp_st);
			x += 9;
		}
	}
}

/****** Load all fonts to be used in-game via XGL ******/
bool Scene::load_game_fonts(std::string font_file)
{

	/* Attempt to load XGL font list to temporary vector */
	std::vector <std::string> temp_vec;
	if(!parse_xgl_string(font_file, temp_vec))
	{
		std::cout<<"The font list file : " << font_file << " failed to load\n";
		return false;
	}

	/* Generate fonts for internal map */
	for(int x = 0; x < temp_vec.size();)
	{
		TTF_Font* temp_font = TTF_OpenFont(temp_vec[x+1].c_str(), 24);
		if(temp_font == NULL) 
		{
			std::cout<<"Unable to open font" << temp_vec[x+1] << " \n";	
			return false;
		}

		font_list[temp_vec[x]] = temp_font;
		x += 2;
	}
}

/****** Render all scene elements ******/		
void Scene::render()
{
	/* Perform animations before drawing operations */
	animator.animate_sprite_translations(sprite_list);

	std::map <std::string, Sprite>::iterator sprite_itr;
	for(sprite_itr = sprite_list.begin(); sprite_itr != sprite_list.end(); sprite_itr++) { (*sprite_itr).second.draw(); }
	for(int x = -1; ++x < text_list.size();) { text_list[x].draw(); }
}

/****** Change scene if in specified range ******/
void Scene::check_scene_ranges()
{


	for(int x = -1; ++x < scene_range_list.size();)
	{
		std::string tgt = scene_range_list[x].target;
		std::string s_file = scene_range_list[x].next_scene_file;
		
		/* Check bounding box */
		if((sprite_list[tgt].orig_x <= scene_range_list[x].max_x) && (sprite_list[tgt].orig_x >= scene_range_list[x].min_x) && 
		(sprite_list[tgt].orig_y <= scene_range_list[x].max_y) && (sprite_list[tgt].orig_y >= scene_range_list[x].min_y)) { load_scene(s_file); }
	}

	for(int x = -1; ++x < scene_button_range_list.size();)
	{
		std::string tgt = scene_button_range_list[x].target;
		bool collide = true;
		
		if(sprite_list[tgt].left_bound() > scene_button_range_list[x].max_x) { collide = false; }
		if(sprite_list[tgt].right_bound() < scene_button_range_list[x].min_x) { collide = false; }
		if(sprite_list[tgt].top_bound() > scene_button_range_list[x].max_y) { collide = false; }
		if(sprite_list[tgt].bottom_bound() < scene_button_range_list[x].min_y) { collide = false; }

		scene_button_range_list[x].in_range = collide;
	}
}
