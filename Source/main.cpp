#include "Core/init.h"
#include "Core/game_state.h"
#include "Graphics/scene.h"

int main(int argc, char* args[]){

	/* Game States */
	game_state g_state = OVERWORLD;

	/* Parse Command Line Arguments */
	for(int x = 0; x++ < argc - 1;) 
	{ 
		std::string temp_arg = args[x]; 
		parse_cli_args(temp_arg);
	}

	/* Initialize Core Systems */
	if(init() == false) { return 1; }

	/* Game Variables */
	SDL_Event event;
	Scene main_scene;

	var::quit = true;

	/****** Main Game Loop ******/        
	while(var::quit == false)
	{

		/****** Get Most Current Time ******/
		var::frame_start_time = SDL_GetTicks();

		/****** Draw Sprites ******/
		if(gfx::hw_accel) { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

		main_scene.check_scene_ranges();
		main_scene.render();

		/****** Check for Key & System input ******/    
		while(SDL_PollEvent(&event)) { var::quit = handle_input(event, main_scene); }

		/****** Update Screen And Frame Counts ******/
		if(gfx::hw_accel) { SDL_GL_SwapBuffers(); }
		else { SDL_Flip(gfx::main_screen); }
		var::frame_count++;
		var::frame_current_time = SDL_GetTicks();

		/****** Frame Rate Handle ******/
		if((var::frame_current_time - var::frame_start_time) < (1000/60)) 
		{
			var::frame_count = 0;
			SDL_Delay((1000/60) - (var::frame_current_time - var::frame_start_time));
		}
	}

	/* Clean Up */
	TTF_Quit(); 
	SDL_Quit(); 

	return 0;    
}
