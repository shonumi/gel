/****** Input **********/
/****** Handles All Input Actions From Keyboards & Joysticks ******/

#ifndef INPUT
#define INPUT

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"
#include "Graphics/sprite.h"
#include "Graphics/gfx_manager.h"
#include "Graphics/scene.h"
#include "Core/game_state.h"

bool handle_input(SDL_Event &event, Scene &current_scene);
bool load_controller_config(std::string filename);

void move_player_overworld(Sprite &player, Scene &current_scene);

namespace ctrl
{
	/* Booleans are for if a button has been pressed, Ints are for pad #s */
	extern bool left, right, up, down, button1, button2;
	extern int left_pad, right_pad, up_pad, down_pad, button1_pad, button2_pad;
}

#endif // INPUT