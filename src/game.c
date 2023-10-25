#include <stdlib.h>
#include <time.h>

#include "include_sdl2.h"

#include "consts.h"

#include "game_type.h"
#include "point_type.h"

#include "game_methods.h"
#include "point_methods.h"
#include "ui_methods.h"
#include "graphics_methods.h"
#include "board_methods.h"

static bool handle_events( Game *self );
static bool update( Game *self );
static void draw( const Game *self );

void game_init( Game *self, int board_cols, int board_rows, int mine_count )
{
	SDL_SetMainReady();
	SDL_SetHint( SDL_HINT_WINDOWS_DPI_AWARENESS, "permonitorv2" );
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	
	self->window = SDL_CreateWindow( WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0 );
	self->renderer = SDL_CreateRenderer( self->window, -1, 0 );
	
	srand( ( unsigned int ) time(nullptr) );
	
	board_init( &self->board, board_cols, board_rows, mine_count );
	ui_init( &self->ui, WINDOW_WIDTH, WINDOW_HEIGHT );
	graphics_init( &self->graphics, self->renderer );
}

void game_destroy( Game *self )
{
	graphics_destroy(&self->graphics);
	ui_destroy(&self->ui);
	board_destroy(&self->board);
	
	SDL_DestroyRenderer(self->renderer);
	self->renderer = nullptr;
	
	SDL_DestroyWindow(self->window);
	self->window = nullptr;
	
	IMG_Quit();
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
			
			case SDL_MOUSEMOTION:
			{
				WindowPoint mouse_position = window_point_new( event.motion.x, event.motion.y );
				ui_on_mouse_move( &self->ui, &self->board, mouse_position );
			}
			break;
			
			case SDL_MOUSEBUTTONDOWN:
			{
				WindowPoint mouse_position = window_point_new( event.button.x, event.button.y );
				
				if ( event.button.button == SDL_BUTTON_LEFT )
				{
					ui_on_left_mouse_down( &self->ui, &self->board, mouse_position );
				}
				else if ( event.button.button == SDL_BUTTON_RIGHT )
				{
					ui_on_right_mouse_down( &self->ui, &self->board, mouse_position );
				}
			}
			break;
			
			case SDL_MOUSEBUTTONUP:
			{
				WindowPoint mouse_position = window_point_new( event.button.x, event.button.y );
				
				if ( event.button.button == SDL_BUTTON_LEFT )
				{
					ui_on_left_mouse_up( &self->ui, &self->board, mouse_position );
				}
				else if ( event.button.button == SDL_BUTTON_RIGHT )
				{
					// Nothing interesting happens.
				}
			}
			break;
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
	graphics_draw( &self->graphics, self->renderer, &self->ui, &self->board );
}