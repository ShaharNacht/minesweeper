#include <stdint.h>

#include "include_sdl2.h"

#include "consts.h"
#include "board.h"

#include "graphics.h"

static void set_color( SDL_Renderer *renderer, const uint8_t *rgb );
static void draw_background( const Graphics *self, SDL_Renderer *renderer, int cols, int rows );
static void draw_board( const Graphics *self, SDL_Renderer *renderer, const Board *board );

void graphics_init( Graphics *self, SDL_Renderer *renderer, int window_width, int window_height )
{
	self->window_width = window_width;
	self->window_height = window_height;
	
	self->cell_texture = IMG_LoadTexture( renderer, GFX_CELL_TEXTURE_PATH );
	self->mine_texture = IMG_LoadTexture( renderer, GFX_MINE_TEXTURE_PATH );
}

void graphics_destroy( Graphics *self )
{
	SDL_DestroyTexture(self->cell_texture);
	self->cell_texture = nullptr;
	
	SDL_DestroyTexture(self->mine_texture);
	self->mine_texture = nullptr;
}

void graphics_draw( const Graphics *self, SDL_Renderer *renderer, const Board *board )
{
	draw_background( self, renderer, board->cols, board->rows );
	draw_board( self, renderer, board );
	
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

static void draw_board( const Graphics *self, SDL_Renderer *renderer, const Board *board )
{
	for ( int y = 0; y < board->rows; y++ )
	{
		for ( int x = 0; x < board->cols; x++ )
		{
			Cell *cell = board_get_cell( board, x, y );
			bool draw_cell = false;
			SDL_Texture *texture = nullptr;
			
			if (!cell->is_revealed)
			{
				draw_cell = true;
				texture = self->cell_texture;
			}
			else if (cell->is_mine)
			{
				draw_cell = true;
				texture = self->mine_texture;
			}
			
			if (draw_cell)
			{
				SDL_RenderCopy(
					renderer,
					texture,
					nullptr,
					&(SDL_Rect) { x * self->window_width / board->cols, y * self->window_height / board->rows, self->window_width / board->cols, self->window_height / board->rows }
				);
			}
		}
	}
}