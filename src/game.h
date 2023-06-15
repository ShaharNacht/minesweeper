#pragma once

#include "include_sdl2.h"

#include "board.h"

typedef struct Game
{
	// read-only
	Board board;
	
	// private
	SDL_Window *window;
} Game;

void game_new( Game *self, int board_cols, int board_rows );
void game_destroy( Game *self );

void game_main_loop( Game *self );