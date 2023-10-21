#include <assert.h>
#include <stdlib.h>

#include "board_type.h"
#include "cell_type.h"
#include "point_type.h"

#include "board_methods.h"
#include "cell_methods.h"

void board_init( Board *self, int cols, int rows )
{
	self->cols = cols;
	self->rows = rows;
	
	bool *mines = malloc( sizeof(bool) * (size_t)self->cols * (size_t)self->rows );
	assert( mines != nullptr );
	for ( int i = 0; i < self->cols * self->rows; i++ )
	{
		mines[i] = ( rand() % 2 ) != 0;
	}
	
	self->cells = malloc( sizeof(Cell) * (size_t)self->cols * (size_t)self->rows );
	assert( self->cells != nullptr );
	for ( int y = 0; y < self->rows; y++ )
	{
		for ( int x = 0; x < self->cols; x++ )
		{
			int i = y * self->cols + x;
			
			int mine_neighbor_count = 0;
			for ( int dy = -1; dy <= 1; dy++ )
			{
				for ( int dx = -1; dx <= 1; dx++ )
				{
					if (
						!( dx == 0 && dy == 0 ) &&
						( x + dx >= 0 ) &&
						( x + dx < self->cols ) &&
						( y + dy >= 0 ) &&
						( y + dy < self->rows ) &&
						mines[ ( y + dy ) * self->cols + ( x + dx ) ]
					)
					{
						mine_neighbor_count++;
					}
				}
			}
			
			cell_init( &self->cells[i], mines[i], mine_neighbor_count );
		}
	}
	
	free(mines);
	mines = nullptr;
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