#include "include_sdl2.h"

#include "consts.h"
#include "board.h"

#include "graphics.h"

static void draw_board( const Graphics *self, SDL_Renderer *renderer, const Board *board );

void graphics_new( Graphics *self, int window_width, int window_height )
{
	self->window_width = window_width;
	self->window_height = window_height;
}

void graphics_destroy( [[maybe_unused]] Graphics *self )
{
	// Intentional no-op, so that this function can already be called wherever necessary,
	// in case code will be added to it in th future.
}

void graphics_draw( const Graphics *self, SDL_Renderer *renderer, const Board *board )
{
	draw_board( self, renderer, board );
	
	SDL_RenderPresent(renderer);
}

static void draw_board( const Graphics *self, SDL_Renderer *renderer, const Board *board )
{
	SDL_SetRenderDrawColor( renderer, GFX_BACKGROUND_COLOR[0], GFX_BACKGROUND_COLOR[1], GFX_BACKGROUND_COLOR[2], SDL_ALPHA_OPAQUE );
	SDL_RenderClear(renderer);
	
	SDL_SetRenderDrawColor( renderer, GFX_GRID_COLOR[0], GFX_GRID_COLOR[1], GFX_GRID_COLOR[2], SDL_ALPHA_OPAQUE );
	for ( int i = 0; i <= board->cols; i++ )
	{
		int x = self->window_width * i / board->cols;
		SDL_RenderFillRect(
			renderer,
			&(SDL_Rect) { x - GFX_GRID_LINE_THICKNESS / 2, 0, GFX_GRID_LINE_THICKNESS, self->window_height }
		);
	}
	for ( int i = 0; i <= board->rows; i++ )
	{
		int y = self->window_height * i / board->rows;
		SDL_RenderFillRect(
			renderer,
			&(SDL_Rect) { 0, y - GFX_GRID_LINE_THICKNESS / 2, self->window_width, GFX_GRID_LINE_THICKNESS }
		);
	}
}