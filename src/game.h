#pragma once

#include "include_sdl2.h"

typedef struct Game
{
	SDL_Window *window;
} Game;

void game_new( Game *self, int board_cols, int board_rows );
void game_destroy( Game *self );

void game_main_loop( Game *self );