#pragma once

#include "include_sdl2.h"

typedef struct Graphics
{
	// read-only
	int window_width;
	int window_height;
	
	// private
	SDL_Texture *cell_texture;
	SDL_Texture *mine_texture;
	SDL_Texture *numbers_texture;
} Graphics;