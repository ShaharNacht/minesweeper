#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

#include "board_type.h"
#include "cell_type.h"
#include "point_type.h"

#include "board_methods.h"
#include "point_methods.h"
#include "cell_methods.h"

static void generate( Board *self, BoardPoint reveal_position );
static void flood_reveal( Board *self, BoardPoint reveal_position );

void board_init( Board *self, int cols, int rows, int mine_count )
{
	self->cols = cols;
	self->rows = rows;
	self->mine_count = mine_count;
	
	self->is_generated = false;
	
	self->cells = malloc( sizeof(Cell) * (size_t)self->cols * (size_t)self->rows );
	assert( self->cells != nullptr );
	
	for ( int y = 0; y < self->rows; y++ )
	{
		for ( int x = 0; x < self->cols; x++ )
		{
			cell_init( &self->cells[ y * self->cols + x ], board_point_new( x, y ) );
		}
	}
}

void board_destroy( Board *self )
{
	for ( int i = 0; i < self->cols * self->rows; i++ )
	{
		cell_destroy( &self->cells[i] );
	}
	
	free(self->cells);
	self->cells = nullptr;
}

Cell *board_get_cell( const Board *self, BoardPoint position )
{
	return &self->cells[ position.y * self->cols + position.x ];
}

void board_reveal_cell( Board *self, Cell *cell )
{
	if (!self->is_generated)
	{
		generate( self, cell->position );
	}
	
	cell->is_revealed = true;
	
	if ( cell->mine_neighbor_count == 0 && !cell->is_mine )
	{
		flood_reveal( self, cell->position );
	}
}

static void generate( Board *self, BoardPoint reveal_position )
{
	BoardPoint *possible_mine_positions = malloc( sizeof(BoardPoint) * (size_t)self->cols * (size_t)self->rows );
	assert( possible_mine_positions != nullptr );
	int possible_mine_positions_length = 0;
	
	for ( int y = 0; y < self->rows; y++ )
	{
		for ( int x = 0; x < self->cols; x++ )
		{
			if ( abs( reveal_position.x - x ) > 1 || abs( reveal_position.y - y ) > 1 )
			{
				possible_mine_positions[possible_mine_positions_length++] = board_point_new( x, y );
			}
		}
	}
	
	bool *mines = malloc( sizeof(bool) * (size_t)self->cols * (size_t)self->rows );
	assert( mines != nullptr );
	int *mine_neighbor_counts = malloc( sizeof(int) * (size_t)self->cols * (size_t)self->rows );
	assert( mine_neighbor_counts != nullptr );
	
	for ( int i = 0; i < self->cols * self->rows; i++ )
	{
		mines[i] = false;
		mine_neighbor_counts[i] = 0;
	}
	
	for ( int i = 0; i < self->mine_count; i++ )
	{
		int mine_index = random_range( 0, possible_mine_positions_length );
		BoardPoint mine_position = possible_mine_positions[mine_index];
		memmove( &possible_mine_positions[mine_index], &possible_mine_positions[ mine_index + 1 ], sizeof(BoardPoint) * (size_t)( possible_mine_positions_length - 1 - mine_index ) );
		possible_mine_positions_length--;
		
		mines[ mine_position.y * self->cols + mine_position.x ] = true;
		
		for ( int y = mine_position.y - 1; y <= mine_position.y + 1; y++ )
		{
			for ( int x = mine_position.x - 1; x <= mine_position.x + 1; x++ )
			{
				if ( x >= 0 && x < self->cols && y >= 0 && y < self->rows )
				{
					mine_neighbor_counts[ y * self->cols + x ]++;
				}
			}
		}
	}
	
	for ( int i = 0; i < self->cols * self->rows; i++ )
	{
		cell_generate( &self->cells[i], mines[i], mine_neighbor_counts[i] );
	}
	
	free(mine_neighbor_counts);
	mine_neighbor_counts = nullptr;
	free(mines);
	mines = nullptr;
	free(possible_mine_positions);
	possible_mine_positions = nullptr;
	
	self->is_generated = true;
}

static void flood_reveal( Board *self, BoardPoint reveal_position )
{
	Cell *cell = board_get_cell( self, reveal_position );
	
	if ( cell->mine_neighbor_count == 0 && !cell->is_mine )
	{
		for ( int dy = -1; dy <= 1; dy++ )
		{
			for ( int dx = -1; dx <= 1; dx++ )
			{
				if (
					!( dx == 0 && dy == 0 ) &&
					reveal_position.x + dx >= 0 &&
					reveal_position.x + dx < self->cols &&
					reveal_position.y + dy >= 0 &&
					reveal_position.y + dy < self->rows
				)
				{
					Cell *neighbor = board_get_cell( self, board_point_new( reveal_position.x + dx, reveal_position.y + dy ) );
					
					if ( !neighbor->is_revealed )
					{
						neighbor->is_revealed = true;
						
						if ( neighbor->mine_neighbor_count == 0 && !neighbor->is_mine )
						{
							flood_reveal( self, neighbor->position );
						}
					}
				}
			}
		}
	}
}