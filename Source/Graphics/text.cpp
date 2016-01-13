/****** Text Class - Class For Textual Rendering **********/
/****** Handles The Displaying Of Text On Screen - Derived From Sprite ******/

#include "text.h"

Text::Text() { }

Text::Text(double x_pos, double y_pos, int delay, std::string txt, TTF_Font* source_font) 
{
	x = x_pos;
	y = y_pos;
	orig_x = x_pos;
	orig_y = y_pos;
	origin_x = x;

	set_font(source_font);

	render_text = txt;
	chop_text = "";

	internal_interval = delay;
	internal_timer = SDL_GetTicks() - internal_interval;
	internal_counter = 1;
	text_position = "LEFT";
	
	text_color.r = 255;
	text_color.g = 255;
	text_color.b = 255;
}

Text::Text(double x_pos, double y_pos, int delay, std::string txt, TTF_Font* source_font, std::string t_pos) 
{
	x = x_pos;
	y = y_pos;
	orig_x = x_pos;
	orig_y = y_pos;
	origin_x = x;

	set_font(source_font);

	render_text = txt;
	chop_text = "";

	internal_interval = delay;
	internal_timer = SDL_GetTicks() - internal_interval;
	internal_counter = 1;
	text_position = t_pos;

	text_color.r = 255;
	text_color.g = 255;
	text_color.b = 255;
}


Text::~Text() { }

/****** Loads Texture From SDL Surface ******/
bool Text::load_texture() 
{
	if(current_surface != NULL)
	{
		glGenTextures(1, &current_texture);
		glBindTexture(GL_TEXTURE_2D, current_texture);
		glTexImage2D(GL_TEXTURE_2D, 0, 4, current_surface->w, current_surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, current_surface->pixels);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		width = current_surface->w;
		height = current_surface->h;

		return true;
	}

	else 
	{ 
		std::cout<<"Texture failed to load from surface\n"; 
		return false;
	}
}

/****** Renders Text Based On Timers ******/
void Text::draw()
{

	/* Check Current Time - Display Updated Text If Interval Has Passed */
	if(((SDL_GetTicks() - internal_timer) >= internal_interval) && (internal_counter <= render_text.length()) && (internal_interval != 0))
	{
		chop_text = "";
		
		for(int x = -1; ++x < internal_counter;) 
		{
			char temp = render_text[x];
			chop_text += temp;
		}

		internal_counter++;
		internal_timer = SDL_GetTicks();
	}

	/* If Interval Is Set To Zero - Display Text At Once */
	else if(internal_interval == 0) { chop_text = render_text; }
		
	current_surface = TTF_RenderText_Blended(font, chop_text.c_str(), text_color);
	orig_w = current_surface->w;
	orig_h = current_surface->h;
	load_texture();

	/* Align Text To The Left */
	if(text_position == "LEFT") { x = (origin_x + (width/2.0)); }	

	/* Align Text To The Right */
	else if(text_position == "RIGHT") { x = (origin_x - (width/2.0)); }

	/* Align Text To Center */
	else if(text_position == "CENTER") { x = origin_x; }

	/* Draw Using OpenGL */
	if(gfx::hw_accel) 
	{
		/* Handle Sprite Scaling First */
		width = orig_w * Sprite::x_ratio;
		height = orig_h * Sprite::y_ratio;
		x = orig_x * x_ratio;
		y = orig_y * y_ratio;

		glTranslatef(x, y, 0);
		glRotatef(rotate, 0, 0, 1);

		glBindTexture(GL_TEXTURE_2D, current_texture);
		glBegin(GL_QUADS);

		glTexCoord2i(0, 0);
		glVertex3f(-width/2, -height/2, 0);

		glTexCoord2i(1, 0);
		glVertex3f(width/2, -height/2, 0);

		glTexCoord2i(1, 1);
		glVertex3f(width/2, height/2, 0);

		glTexCoord2i(0, 1);
		glVertex3f(-width/2, height/2, 0);
		glEnd();

		glLoadIdentity();
	}

	/* Draw Using SDL */
	else 
	{
		SDL_Rect offset;

		offset.x = x - (current_surface->w/2);
		offset.y = y - (current_surface->h/2);
    
		SDL_BlitSurface(current_surface, NULL, gfx::main_screen, &offset);
	}
} 


/****** Sets Font For Text Instance ******/
void Text::set_font(TTF_Font* source_font)  { font = source_font; }