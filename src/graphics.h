#pragma once

#include "include_sdl2.h"

#include "board.h"

typedef struct Graphics
{
	// private
	int window_width;
	int window_height;
} Graphics;

void graphics_new( Graphics *self, int window_width, int window_height );
void graphics_destroy( Graphics *self );

void graphics_draw( const Graphics *self, SDL_Renderer *renderer, const Board *board );