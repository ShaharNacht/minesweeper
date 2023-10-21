#pragma once

#include "cell_type.h"

typedef struct Board
{
	// read-only
	int cols;
	int rows;
	Cell *cells;
} Board;