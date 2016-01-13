/****** Text Class - Class For Textual Rendering **********/
/****** Handles The Displaying Of Text On Screen - Derived From Sprite ******/


#ifndef GRAPHICS_TEXT
#define GRAPHICS_TEXT

#include "SDL/SDL_ttf.h"
#include "sprite.h"

class Text : virtual public Sprite
{
	public:

	std::string render_text;
	std::string chop_text;
	std::string text_position;

	SDL_Color text_color;

	int internal_timer;
	int internal_counter;
	int internal_interval;
	double origin_x;

	TTF_Font* font;

	Text();
	Text(double x_pos, double y_pos, int delay, std::string txt, TTF_Font* source_font);
	Text(double x_pos, double y_pos, int delay, std::string txt, TTF_Font* source_font, std::string t_pos);
	~Text();

	bool load_texture();
	void draw();
	void set_font(TTF_Font* source_font);
};

#endif // GRAPHICS_TEXT
