#include <stddef.h>
#include <stdbool.h>

#include "include_sdl2.h"

#include "consts.h"
#include "board.h"
#include "graphics.h"

#include "game.h"

static bool handle_events( Game *self );
static bool update( Game *self );
static void draw( const Game *self );

void game_new( Game *self, int board_cols, int board_rows )
{
	SDL_SetMainReady();
	SDL_SetHint( SDL_HINT_WINDOWS_DPI_AWARENESS, "permonitorv2" );
	SDL_Init(SDL_INIT_VIDEO);
	
	self->window = SDL_CreateWindow( "Minesweeper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0 );
	self->renderer = SDL_CreateRenderer( self->window, -1, 0 );
	
	board_new( &self->board, board_cols, board_rows );
	graphics_new( &self->graphics, WINDOW_WIDTH, WINDOW_HEIGHT );
}

void game_destroy( Game *self )
{
	graphics_destroy(&self->graphics);
	board_destroy(&self->board);
	
	SDL_DestroyRenderer(self->renderer);
	self->renderer = NULL;
	
	SDL_DestroyWindow(self->window);
	self->window = NULL;
	
	SDL_Quit();
}

void game_main_loop( Game *self )
{
	bool keep_running = true;
	
	while (keep_running)
	{
		keep_running = handle_events(self);
		if (!keep_running)
		{
			break;
		}
		
		keep_running = update(self);
		if (!keep_running)
		{
			break;
		}
		
		draw(self);
		
		SDL_Delay( 1000 / TARGET_FPS );
	}
}

static bool handle_events( Game *self )
{
	SDL_Event event;
	while ( SDL_PollEvent(&event) )
	{
		switch (event.type)
		{
			case SDL_QUIT:
				return false;
		}
	}
	
	return true;
}

static bool update( Game *self )
{
	return true;
}

static void draw( const Game *self )
{
	graphics_draw( &self->graphics, self->renderer, &self->board );
}