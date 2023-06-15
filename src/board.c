#include "board.h"

void board_new( Board *self, int cols, int rows )
{
	self->cols = cols;
	self->rows = rows;
}

void board_destroy( Board *self )
{
	
}