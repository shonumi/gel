/****** Scene Class - Class For Graphical Scenes **********/
/****** Handles Loading And Managing Individual Scenes ******/

#ifndef GRAPHICS_SCENE
#define GRAPHICS_SCENE 

#include <map>
#include "sprite.h"
#include "text.h"
#include "construct.h"
#include "animation.h"
#include "Core/xgl.h"

struct scene_button
{
	std::string next_scene_file;
	std::string pad;
};

struct scene_range
{
	std::string next_scene_file;
	std::string target;
	double min_x, max_x;
	double min_y, max_y;
};

struct scene_button_range
{
	std::string next_scene_file;
	std::string pad;
	std::string target;
	double min_x, max_x;
	double min_y, max_y;
	bool in_range;
};

class Scene
{
	public : 

	std::map <std::string, Sprite> sprite_list;
	std::vector <Text> text_list;
	std::map <std::string, TTF_Font*> font_list;
	std::vector <Construct> construct_list;

	std::vector <scene_button> scene_button_list;
	std::vector <scene_range> scene_range_list;
	std::vector <scene_button_range> scene_button_range_list;

	Animation animator;

	Scene();
	~Scene();

	bool load_scene(std::string scene_file);
	bool load_game_fonts(std::string font_file);
	void render();
	
	void check_scene_ranges();
};

#endif // GRAPHICS_SCENE