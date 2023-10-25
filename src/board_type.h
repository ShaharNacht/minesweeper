#pragma once

#include "cell_type.h"

typedef struct Board
{
	// read-only
	int cols;
	int rows;
	int mine_count;
	Cell *cells;
	
	// private
	bool is_generated;
} Board;