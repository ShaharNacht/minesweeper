#pragma once

#include "include_sdl2.h"

#include "ui.h"
#include "board.h"
#include "graphics.h"

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

void game_init( Game *self, int board_cols, int board_rows );
void game_destroy( Game *self );

void game_main_loop( Game *self );