#pragma once

#include "include_sdl2.h"

#include "ui_type.h"
#include "graphics_type.h"
#include "board_type.h"

typedef struct Game
{
	// read-only
	Board board;
	
	// private
	Ui ui;
	Graphics graphics;
	SDL_Window *window;
	SDL_Renderer *renderer;
} Game;