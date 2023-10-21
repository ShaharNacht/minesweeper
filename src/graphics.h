#pragma once

typedef struct Ui Ui; // Prevent cyclic dependency

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

#include "ui.h"
#include "board.h"

void graphics_init( Graphics *self, SDL_Renderer *renderer, int window_width, int window_height );
void graphics_destroy( Graphics *self );

void graphics_draw( const Graphics *self, SDL_Renderer *renderer, const Ui *ui, const Board *board );