#include <stdlib.h>

#include "cell.h"
#include "point.h"

#include "board.h"

void board_init( Board *self, int cols, int rows )
{
	self->cols = cols;
	self->rows = rows;
	
	self->cells = malloc( sizeof(Cell) * self->cols * self->rows );
	for ( int i = 0; i < self->cols * self->rows; i++ )
	{
		cell_init( &self->cells[i] );
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