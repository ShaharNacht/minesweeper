#include <stdint.h>

#include "include_sdl2.h"

#include "consts.h"

#include "graphics_type.h"
#include "ui_type.h"
#include "point_type.h"
#include "board_type.h"
#include "cell_type.h"

#include "graphics_methods.h"
#include "point_methods.h"
#include "ui_methods.h"
#include "board_methods.h"

static void set_color( SDL_Renderer *renderer, const uint8_t *rgb );
static void draw_background( SDL_Renderer *renderer, const Ui *ui, const Board *board );
static void draw_board( const Graphics *self, SDL_Renderer *renderer, const Ui *ui, const Board *board );

void graphics_init( Graphics *self, SDL_Renderer *renderer )
{
	self->cell_texture = IMG_LoadTexture( renderer, GFX_CELL_TEXTURE_PATH );
	self->mine_texture = IMG_LoadTexture( renderer, GFX_MINE_TEXTURE_PATH );
	self->numbers_texture = IMG_LoadTexture( renderer, GFX_NUMBERS_TEXTURE_PATH );
}

void graphics_destroy( Graphics *self )
{
	SDL_DestroyTexture(self->cell_texture);
	self->cell_texture = nullptr;
	
	SDL_DestroyTexture(self->mine_texture);
	self->mine_texture = nullptr;
	
	SDL_DestroyTexture(self->numbers_texture);
	self->numbers_texture = nullptr;
}

void graphics_draw( const Graphics *self, SDL_Renderer *renderer, const Ui *ui, const Board *board )
{
	draw_background( renderer, ui, board );
	draw_board( self, renderer, ui, board );
	
	SDL_RenderPresent(renderer);
}

static void set_color( SDL_Renderer *renderer, const uint8_t *rgb )
{
	SDL_SetRenderDrawColor( renderer, rgb[0], rgb[1], rgb[2], SDL_ALPHA_OPAQUE );
}

static void draw_background( SDL_Renderer *renderer, const Ui *ui, const Board *board )
{
	set_color( renderer, GFX_BACKGROUND_COLOR );
	SDL_RenderClear(renderer);
	
	set_color( renderer, GFX_GRID_COLOR );
	for ( int i = 0; i <= board->cols; i++ )
	{
		BoardPoint board_point = board_point_new( i, 0 );
		WindowPoint window_point = board_point_to_window_point( board_point, ui, board );
		
		SDL_RenderFillRect(
			renderer,
			&(SDL_Rect) { window_point.x - GFX_GRID_LINE_THICKNESS / 2, 0, GFX_GRID_LINE_THICKNESS, ui->window_height }
		);
	}
	for ( int i = 0; i <= board->rows; i++ )
	{
		BoardPoint board_point = board_point_new( 0, i );
		WindowPoint window_point = board_point_to_window_point( board_point, ui, board );
		
		SDL_RenderFillRect(
			renderer,
			&(SDL_Rect) { 0, window_point.y - GFX_GRID_LINE_THICKNESS / 2, ui->window_width, GFX_GRID_LINE_THICKNESS }
		);
	}
}

static void draw_board( const Graphics *self, SDL_Renderer *renderer, const Ui *ui, const Board *board )
{
	for ( int y = 0; y < board->rows; y++ )
	{
		for ( int x = 0; x < board->cols; x++ )
		{
			BoardPoint board_point = board_point_new( x, y );
			Cell *cell = board_get_cell( board, board_point );
			WindowPoint window_point = board_point_to_window_point( board_point, ui, board );
			int cell_width = ui_get_cell_width( ui, board );
			int cell_height = ui_get_cell_height( ui, board );
			
			if (!cell->is_revealed)
			{
				SDL_RendererFlip flip;
				if ( ui->selected_cell == cell && ui->is_mouse_on_selected_cell )
				{
					flip = SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL;
				}
				else
				{
					flip = SDL_FLIP_NONE;
				}
				
				SDL_RenderCopyEx(
					renderer,
					self->cell_texture,
					nullptr,
					&(SDL_Rect) { window_point.x, window_point.y, cell_width, cell_height },
					0.0,
					nullptr,
					flip
				);
			}
			else if (cell->is_mine)
			{
				SDL_RenderCopy(
					renderer,
					self->mine_texture,
					nullptr,
					&(SDL_Rect) { window_point.x, window_point.y, cell_width, cell_height }
				);
			}
			else
			{
				int numbers_texture_width;
				int numbers_texture_height;
				SDL_QueryTexture( self->numbers_texture, nullptr, nullptr, &numbers_texture_width, &numbers_texture_height );
				int src_x = cell->mine_neighbor_count * numbers_texture_width / GFX_NUMBERS_TEXTURE_SUBTEXTURE_COUNT;
				int src_width = numbers_texture_width / GFX_NUMBERS_TEXTURE_SUBTEXTURE_COUNT;
				
				SDL_RenderCopy(
					renderer,
					self->numbers_texture,
					&(SDL_Rect) { src_x, 0, src_width, numbers_texture_height },
					&(SDL_Rect) { window_point.x, window_point.y, cell_width, cell_height }
				);
			}
		}
	}
}