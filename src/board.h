#pragma once

typedef struct BoardPoint BoardPoint; // Prevent cyclic dependency

#include "cell.h"
#include "point.h"

typedef struct Board
{
	// read-only
	int cols;
	int rows;
	Cell *cells;
} Board;

void board_init( Board *self, int cols, int rows );
void board_destroy( Board *self );

Cell *board_get_cell( const Board *self, BoardPoint position );