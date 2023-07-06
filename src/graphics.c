#include <stdint.h>

#include "include_sdl2.h"

#include "consts.h"
#include "board.h"
#include "point.h"

#include "graphics.h"

static void set_color( SDL_Renderer *renderer, const uint8_t *rgb );
static void draw_background( const Graphics *self, SDL_Renderer *renderer, const Board *board );
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
	draw_background( self, renderer, board );
	draw_board( self, renderer, board );
	
	SDL_RenderPresent(renderer);
}

static void set_color( SDL_Renderer *renderer, const uint8_t *rgb )
{
	SDL_SetRenderDrawColor( renderer, rgb[0], rgb[1], rgb[2], SDL_ALPHA_OPAQUE );
}

static void draw_background( const Graphics *self, SDL_Renderer *renderer, const Board *board )
{
	set_color( renderer, GFX_BACKGROUND_COLOR );
	SDL_RenderClear(renderer);
	
	set_color( renderer, GFX_GRID_COLOR );
	for ( int i = 0; i <= board->cols; i++ )
	{
		BoardPoint board_point = board_point_new( i, 0 );
		WindowPoint window_point = board_point_to_window_point( board_point, board, self );
		
		SDL_RenderFillRect(
			renderer,
			&(SDL_Rect) { window_point.x - GFX_GRID_LINE_THICKNESS / 2, 0, GFX_GRID_LINE_THICKNESS, self->window_height }
		);
	}
	for ( int i = 0; i <= board->rows; i++ )
	{
		BoardPoint board_point = board_point_new( 0, i );
		WindowPoint window_point = board_point_to_window_point( board_point, board, self );
		
		SDL_RenderFillRect(
			renderer,
			&(SDL_Rect) { 0, window_point.y - GFX_GRID_LINE_THICKNESS / 2, self->window_width, GFX_GRID_LINE_THICKNESS }
		);
	}
}

static void draw_board( const Graphics *self, SDL_Renderer *renderer, const Board *board )
{
	for ( int y = 0; y < board->rows; y++ )
	{
		for ( int x = 0; x < board->cols; x++ )
		{
			BoardPoint board_point = board_point_new( x, y );
			Cell *cell = board_get_cell( board, board_point );
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
				WindowPoint window_point = board_point_to_window_point( board_point, board, self );
				int cell_width = window_cell_width( board, self );
				int cell_height = window_cell_height( board, self );
				
				SDL_RenderCopy(
					renderer,
					texture,
					nullptr,
					&(SDL_Rect) { window_point.x, window_point.y, cell_width, cell_height }
				);
			}
		}
	}
}