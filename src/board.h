#pragma once

#include "cell.h"

typedef struct Board
{
	// read-only
	int cols;
	int rows;
	Cell *cells;
} Board;

void board_new( Board *self, int cols, int rows );
void board_destroy( Board *self );

Cell *board_get_cell( const Board *self, int x, int y );