#include <stdlib.h>

#include "cell.h"

#include "board.h"

void board_new( Board *self, int cols, int rows )
{
	self->cols = cols;
	self->rows = rows;
	
	self->cells = malloc( sizeof(Cell) * self->cols * self->rows );
	for ( int i = 0; i < self->cols * self->rows; i++ )
	{
		cell_new( &self->cells[i] );
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