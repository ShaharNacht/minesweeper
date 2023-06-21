#include <stdint.h>

#include "include_sdl2.h"

#include "consts.h"
#include "board.h"

#include "graphics.h"

static void set_color( SDL_Renderer *renderer, const uint8_t *rgb );
static void draw_background( const Graphics *self, SDL_Renderer *renderer, int cols, int rows );
static void draw_board( const Graphics *self, SDL_Renderer *renderer, const Board *board );

void graphics_new( Graphics *self, int window_width, int window_height )
{
	self->window_width = window_width;
	self->window_height = window_height;
}

void graphics_destroy( [[maybe_unused]] Graphics *self )
{
	// Intentional no-op, so that this function can already be called wherever necessary,
	// in case code will be added to it in the future.
}

void graphics_draw( const Graphics *self, SDL_Renderer *renderer, const Board *board )
{
	draw_background( self, renderer, board->cols, board->rows );
	// draw_board( self, renderer, board );
	
	SDL_RenderPresent(renderer);
}

static void set_color( SDL_Renderer *renderer, const uint8_t *rgb )
{
	SDL_SetRenderDrawColor( renderer, rgb[0], rgb[1], rgb[2], SDL_ALPHA_OPAQUE );
}

static void draw_background( const Graphics *self, SDL_Renderer *renderer, int cols, int rows )
{
	set_color( renderer, GFX_BACKGROUND_COLOR );
	SDL_RenderClear(renderer);
	
	set_color( renderer, GFX_GRID_COLOR );
	for ( int i = 0; i <= cols; i++ )
	{
		int x = self->window_width * i / cols;
		SDL_RenderFillRect(
			renderer,
			&(SDL_Rect) { x - GFX_GRID_LINE_THICKNESS / 2, 0, GFX_GRID_LINE_THICKNESS, self->window_height }
		);
	}
	for ( int i = 0; i <= rows; i++ )
	{
		int y = self->window_height * i / rows;
		SDL_RenderFillRect(
			renderer,
			&(SDL_Rect) { 0, y - GFX_GRID_LINE_THICKNESS / 2, self->window_width, GFX_GRID_LINE_THICKNESS }
		);
	}
}

// static void draw_board( const Graphics *self, SDL_Renderer *renderer, const Board *board )
// {
	
// }