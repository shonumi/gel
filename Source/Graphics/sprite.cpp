/****** Sprite Class - Base Class For All Interactive Graphics **********/
/****** Handles Graphics Level Details For Other Derived Classes ******/

#include "sprite.h"

double Sprite::x_ratio = 1.0;
double Sprite::y_ratio = 1.0;

Sprite::Sprite() { }

Sprite::Sprite(double x_pos, double y_pos, double w, double h, std::string image)
{
	x = x_pos;
	y = y_pos;
	width = w;
	height = h;
	current_frame = 0;
	frame_spacer = 0;
	rotate = 0.0;
	load_texture(image);

	orig_x = x_pos;
	orig_y = y_pos;
	orig_w = w;
	orig_h = h;
}

Sprite::~Sprite() { }

/****** Returns the true left boundary of a sprite ******/
double Sprite::left_bound() { 
	if(!clipped) { return orig_x - (orig_w/2);}
	else { return orig_x - (sprite_clip[current_frame].w/2); }
 }

/****** Returns the true right boundary of a sprite ******/
double Sprite::right_bound() { 
	if(!clipped) { return orig_x + (orig_w/2);}
	else { return orig_x + (sprite_clip[current_frame].w/2); }
 }

/****** Returns the true top boundary of a sprite ******/
double Sprite::top_bound() { 
	if(!clipped) { return orig_y - (orig_h/2);}
	else { return orig_y - (sprite_clip[current_frame].h/2); }
 }

/****** Returns the true bottom boundary of a sprite ******/
double Sprite::bottom_bound() { 
	if(!clipped) { return orig_y + (orig_h/2);}
	else { return orig_y + (sprite_clip[current_frame].h/2); }
 }

/****** Loads Texture From Image ******/
bool Sprite::load_texture(std::string image)
{
	/* Set clipped to false when loadng new image */
	clipped = false;

	/* Load to OpenGL Texture */
	if(gfx::hw_accel)
	{
		current_surface = IMG_Load(image.c_str());
    
		if(current_surface != NULL)
		{
			glGenTextures(1, &current_texture);
			glBindTexture(GL_TEXTURE_2D, current_texture);
			glTexImage2D(GL_TEXTURE_2D, 0, 4, current_surface->w, current_surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, current_surface->pixels);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			return true;
		}

		else 
		{ 
			std::cout<<"The image file: " << image << " failed to load \n"; 
			return false;
		}
	}

	/* Load to SDL Surface */
	else { 
		SDL_Surface* sdl_texture = NULL;
		current_surface = NULL;

		sdl_texture = IMG_Load(image.c_str());

		if(sdl_texture != NULL)
		{
			current_surface = SDL_DisplayFormatAlpha(sdl_texture);
			SDL_FreeSurface(sdl_texture);

			if(current_surface != NULL)
			{
				Uint32 color_key = SDL_MapRGB(current_surface->format, 128, 128, 128);            
				SDL_SetColorKey(current_surface, SDL_RLEACCEL | SDL_SRCCOLORKEY, color_key);
				return true;
			}
			
			else 
			{ 
				std::cout<<"The image file: " << image << " failed to load \n"; 
				return false;
			}
		}

		else 
		{ 
			std::cout<<"The image file: " << image << " failed to load \n"; 
			return false;
		}
	}	
}

/****** Loads Clips For Sprite ******/
bool Sprite::load_clips(std::string clip_file)
{
	std::vector <int> temp_vec;
	clip temp_clip;
	
	/* Read all values from file */
	if(!parse_xgl_int(clip_file, temp_vec))
	{
		std::cout<<"The clip file : " << clip_file << " failed to load \n";
		return false;
	}

	/* Clear current clips vector, only if file is loaded, just to be safe */
	sprite_clip.clear();

	/* Transfer values from temporary vector to clip vector */
	for(int x = 0; x < temp_vec.size(); x+=4)
	{
		temp_clip.x = temp_vec[x];
		temp_clip.y = temp_vec[x+1];
		temp_clip.w = temp_vec[x+2];
		temp_clip.h = temp_vec[x+3];
		sprite_clip.push_back(temp_clip);
	}
	
	clipped = true;
	return true;
}

/****** Animate Frame By  Frame ******/
void Sprite::animate(int start, int end, int timing)
{
	frame_spacer++;

	if(frame_spacer > timing) { frame_spacer = 0; }
	
	else if(frame_spacer == timing) { current_frame++; }

	if((current_frame < start) || (current_frame  > end)) { current_frame = start; }
}

/****** Draws Sprite To Screen ******/
void Sprite::draw() 
{
	/* Draw Using OpenGL */
	if(gfx::hw_accel)
	{

		float texture_left, texture_top = 0;
		float texture_right, texture_bottom = 1;

		/* Handle Sprite Scaling */
		width = orig_w * Sprite::x_ratio;
		height = orig_h * Sprite::y_ratio;
		x = orig_x * x_ratio;
		y = orig_y * y_ratio;

		/* Handle Sprite Clipping */
		if(clipped)
		{
			texture_left = sprite_clip[current_frame].x/orig_w;
			texture_right = (sprite_clip[current_frame].x + sprite_clip[current_frame].w)/orig_w;
			texture_top = sprite_clip[current_frame].y/orig_h;
			texture_bottom = (sprite_clip[current_frame].y + sprite_clip[current_frame].h)/orig_h;
			width = sprite_clip[current_frame].w * Sprite::x_ratio;
			height = sprite_clip[current_frame].h * Sprite::y_ratio;
		}

		/* For whatever reason, this works :| */
		else
		{
			texture_left = 0/orig_w;
			texture_right = orig_w/orig_w;
			texture_top = 0/orig_h;
			texture_bottom = orig_h/orig_h;
		}

		glTranslatef(x, y, 0);
		glRotatef(rotate, 0, 0, 1);

		glBindTexture(GL_TEXTURE_2D, current_texture);
		glBegin(GL_QUADS);

		glTexCoord2f(texture_left, texture_top);
		glVertex3f(-width/2, -height/2, 0);

		glTexCoord2f(texture_right, texture_top);
		glVertex3f(width/2, -height/2, 0);

		glTexCoord2f(texture_right, texture_bottom);
		glVertex3f(width/2, height/2, 0);

		glTexCoord2f(texture_left, texture_bottom);
		glVertex3f(-width/2, height/2, 0);
		glEnd();

		glLoadIdentity();
	}

	/* Draw Using SDL */
	else
	{

		if(!clipped)
		{
			SDL_Rect offset;	

			offset.x = orig_x - (current_surface->w/2);
			offset.y = orig_y - (current_surface->h/2);
		
			SDL_BlitSurface(current_surface, NULL, gfx::main_screen, &offset);    
		}

		else
		{
			SDL_Rect offset, clip;	

			clip.x = sprite_clip[current_frame].x;
			clip.y = sprite_clip[current_frame].y;
			clip.w = sprite_clip[current_frame].w;
			clip.h = sprite_clip[current_frame].h;

			offset.x = orig_x - (clip.w/2);
			offset.y = orig_y - (clip.h/2);

			SDL_BlitSurface(current_surface, &clip, gfx::main_screen, &offset);    
		}
	}	
} 
